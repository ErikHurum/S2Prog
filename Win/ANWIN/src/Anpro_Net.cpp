/////////////////////////////////////////////////////////////////////////
//
// ANPRO10 over Network
//
// Revision History
// - 2016/Aug/18 initial release by hkim
//
/////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#ifdef WIN32
#include "windows.h"
#include <functional>
//using namespace std;
#endif
#include "ChildUnit.h"
#include "Anpro_Net.h"
#include "ANWinInc.h"

#include "Mstcpip.h"

#pragma package(smart_init)

Anpro_Net*     Anpro_Net::apnet 	 = NULL;
volatile bool  Anpro_Net::_exit_flag = false;

/////////////////////////////////////////////////////////////////////////
//
// some utilities first
// 
// due to highly stupid nature of windows operating system,
// we need this kind of dirty communication mechanism for inter thread
// communication and I/O multiplexing.
// Please Windows, give up your stupid tenacity or die fast.
// -hkim-
//
/////////////////////////////////////////////////////////////////////////
static SOCKET
ev_tcp_socket(void)
{
   return socket(AF_INET, SOCK_STREAM, 0);
}

static int
ev_pipe(int filedes[2])
{
   struct sockaddr_in addr = { 0 };
   int addr_size = sizeof (addr);
   struct sockaddr_in adr2;
   int adr2_size = sizeof (adr2);
   SOCKET listener;

   SOCKET sock [2] = { -1, -1 };
   if ((listener = ev_tcp_socket ()) == INVALID_SOCKET)
      return -1;

   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
   addr.sin_port = 0;

   if (::bind (listener, (struct sockaddr *)&addr, addr_size))
      goto fail;

   if (getsockname (listener, (struct sockaddr *)&addr, &addr_size))
      goto fail;

   if (listen (listener, 1))
      goto fail;

   if ((sock [0] = ev_tcp_socket ()) == INVALID_SOCKET)
      goto fail;

   if (connect (sock [0], (struct sockaddr *)&addr, addr_size))
      goto fail;

   if ((sock [1] = accept (listener, 0, 0)) == INVALID_SOCKET)
      goto fail;

   if (getpeername (sock [0], (struct sockaddr *)&addr, &addr_size))
      goto fail;

   if (getsockname (sock [1], (struct sockaddr *)&adr2, &adr2_size))
      goto fail;

   errno = WSAEINVAL;
   if (addr_size != adr2_size
      || addr.sin_addr.s_addr != adr2.sin_addr.s_addr /* just to be sure, I mean, it's windows */
      || addr.sin_port        != adr2.sin_port)
      goto fail;

   closesocket (listener);

   filedes [0] = sock [0];
   filedes [1] = sock [1];
  return 0;

fail:
  closesocket (listener);

  if (sock [0] != INVALID_SOCKET) closesocket (sock [0]);
  if (sock [1] != INVALID_SOCKET) closesocket (sock [1]);

  return -1;
}
/////////////////////////////////////////////////////////////////////////
// end of dirty utilities
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//
// real simple timer class
// I just hated porting SGTimer here
//
/////////////////////////////////////////////////////////////////////////
SimpleTimer::SimpleTimer()
{
	startedAt = 0;
	pausedAt = 0;
	paused = false;
	started = false;
}

bool SimpleTimer::IsStarted()
{
	return started;
}

bool SimpleTimer::IsStopped()
{
	return !started;
}

bool SimpleTimer::IsPaused()
{
	return paused;
}

bool SimpleTimer::IsActive()
{
	return !paused & started;
}

void SimpleTimer::Pause()
{
	if( paused || !started )
		return;
	paused = true;
	pausedAt = clock();
}

void SimpleTimer::Resume()
{
	if( !paused )
		return;
	paused = false;
	startedAt += clock() - pausedAt;
}

void SimpleTimer::Stop()
{
	started = false;
}

void SimpleTimer::Start()
{
	if( started )
		return;
	started = true;
	paused = false;
	startedAt = clock();
}

void SimpleTimer::Reset()
{
	paused = false;
	startedAt = clock();
}

clock_t SimpleTimer::GetTicks()
{
	if( !started )
		return 0;
	if( paused )
		return pausedAt - startedAt;
	return clock() - startedAt;
}

/////////////////////////////////////////////////////////////////////////
//
// some common socket utilities
//
/////////////////////////////////////////////////////////////////////////
static int
init_client_socket(void)
{
   int sock;

   sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   struct tcp_keepalive vals;
   DWORD byteRet = 0;

   vals.onoff = TRUE;
   vals.keepalivetime = 10 * 1000;
   vals.keepaliveinterval = 2 * 1000;

   WSAIoctl(sock, SIO_KEEPALIVE_VALS, &vals, sizeof(vals), NULL, 0,
	  &byteRet, NULL, NULL);

   return sock;
}

static void
put_socket_nonblocking(int sock)
{
   u_long      cmd = 1;

   ioctlsocket(sock, FIONBIO, &cmd);
}

static int
init_udp_socket(unsigned short port)
{
   int                     sock;
   struct sockaddr_in      anpro_saddr;

   sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   memset(&anpro_saddr, 0, sizeof(anpro_saddr));
   anpro_saddr.sin_family        = AF_INET;
   anpro_saddr.sin_addr.s_addr   = INADDR_ANY;
   anpro_saddr.sin_port          = htons(port);

   if(::bind(sock, (struct sockaddr*)&anpro_saddr, sizeof(anpro_saddr)) != 0)
   {
      closesocket(sock);
      return -1;
   }

   return sock;
}

/////////////////////////////////////////////////////////////////////////
//
// 
// Anpro10 reader to read in Anpro10 messages from stream
//
/////////////////////////////////////////////////////////////////////////
Anpro10_Reader::Anpro10_Reader(anpro10_reader_callback cb, void* cb_arg)
{
   reset();
   callback           = cb;
   this->cb_arg       = cb_arg;
}

inline void
Anpro10_Reader::reset(void)
{
  state              = ANPRO10_RX_Header;
  buffered_data_len  = 0;
  body_len_to_read   = 0;
}

inline void
Anpro10_Reader::decode(unsigned char in)
{
   bounce_buffer[buffered_data_len++] = in;

   switch(state)
   {
   case ANPRO10_RX_Header:
      // be careful about alignment shit. NetHeading is 7 bytes long. 
      if(buffered_data_len >= sizeof(struct ANPRO10_PacketHeading))
      {
         const struct ANPRO10_PacketHeading* pH = (struct ANPRO10_PacketHeading*)bounce_buffer;
         unsigned char csum;

         csum = calc_csum(bounce_buffer, sizeof(struct ANPRO10_PacketHeading) -1);
         if(csum != pH->HCRC)
         {
            reset();
            return;
         }

         body_len_to_read = pH->nob - sizeof(struct ANPRO10_PacketHeading);
         if(body_len_to_read <= 3)
         {
            // this shift appears to happen with RS485. anyway
            reset();
            return;
         }
         state = ANPRO10_RX_Body;
      }
      break;

   case ANPRO10_RX_Body:
      if(buffered_data_len >= (body_len_to_read + sizeof(struct ANPRO10_PacketHeading)))
      { // bingo. we got the message
         unsigned char csum;
         unsigned char pcsum;

         const struct ANPRO10_PacketHeading* pH = (struct ANPRO10_PacketHeading*)bounce_buffer;

         csum = calc_csum(bounce_buffer, pH->nob - 2);

         pcsum = bounce_buffer[pH->nob -2];
         if(pcsum == csum)
         {
            // another bingo
            callback(this, bounce_buffer, buffered_data_len, cb_arg);
         }
         reset();
      }
	  break;
  }
}

void
Anpro10_Reader::feed(const unsigned char* msg, int len)
{
  int     i;

  for(i = 0; i < len; i++)
  {
    if(buffered_data_len >= ANPRO_READER_BUFFER_SIZE)
    {
       // something is seriously fucked up here.
	   reset();
       continue;
    }
	decode(msg[i]);
  }
}

inline unsigned char
Anpro10_Reader::calc_csum(const unsigned char* msg, int len)
{
  int                i;
  unsigned char      csum = 0;
  extern  const U8   CRC[];

  for(i = 0; i < len; i++)
  {
    csum = CRC[csum ^ msg[i]];
  }

  return csum;
}


#define Anpro_Net_Event_Normal_Message          0
#define Anpro_Net_Event_Urgent_Message          1
#define Anpro_Net_Event_Quit_Message            2

/////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
/////////////////////////////////////////////////////////////////////////
Anpro_Net::Anpro_Net()
   : _tcp_reader(Anpro_Net::anpro_tcp_read_callback, this)
{
   _anpro_net_thread = NULL;
   _tcp_sock         = INVALID_SOCKET;
   _udp_sock         = INVALID_SOCKET;
   _normal_Q         = NULL;
   _urgent_Q         = NULL;

   memset(&_server_tcp_addr, 0, sizeof(_server_tcp_addr));
   _server_tcp_addr.sin_family        = AF_INET;
   if (PROProjectInfo::IP_AddressMain) {
       _server_tcp_addr.sin_addr.s_addr   = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressTCU_Master << 24);
   } else {
       _server_tcp_addr.sin_addr.s_addr   = inet_addr("192.168.227.30");   //ANPRO_NET_TCU_MASTER
   }

   //_server_tcp_addr.sin_addr.s_addr   = inet_addr("192.168.10.171");
   _server_tcp_addr.sin_port          = htons(PROProjectInfo::IP_TCP_ServerPort);//15533

   memset(&_server_udp_addr, 0, sizeof(_server_udp_addr));
   _server_udp_addr.sin_family        = AF_INET;
   if (PROProjectInfo::IP_AddressMain) {
       _server_udp_addr.sin_addr.s_addr   = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressTCU_Master << 24);
   } else {
       _server_udp_addr.sin_addr.s_addr   = inet_addr("192.168.227.30");   //ANPRO_NET_TCU_MASTER
   }
   _server_udp_addr.sin_port          = htons(PROProjectInfo::IP_UDP_NetPort);//15534
}

Anpro_Net::~Anpro_Net()
{
   stop();
}

void
Anpro_Net::send_normal(char* msg, int size)
{
   if(!_normal_Q)
      return;

   _normal_Q->PostMessage(msg, size);
   notify_anpro_thread(Anpro_Net_Event_Normal_Message);
}

void
Anpro_Net::send_urgent(char* msg, int size)
{
   if(!_urgent_Q)
      return;

   _urgent_Q->PostMessage(msg, size);
   notify_anpro_thread(Anpro_Net_Event_Urgent_Message);
}

void
Anpro_Net::start(void)
{
   if(_anpro_net_thread != NULL)
   {
      return;
   }

   _normal_Q = new TSNMessageQ();
   _urgent_Q = new TSNMessageQ();

   ev_pipe(_pipes);

   _anpro_net_thread = ::CreateThread(
         NULL,                            // security attributes
         0,                               // stack size
         Anpro_Net::anpro_net_thread,     // thread routine
         this,                            // lpParameter
         0,                               // creation flags
		 NULL);                           // threadId
   SetThreadPriority(_anpro_net_thread, THREAD_PRIORITY_TIME_CRITICAL);
   if (PROProjectInfo::IP_AddressMain) {
       _server_tcp_addr.sin_addr.s_addr   = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressTCU_Master << 24);
   } else {
       _server_tcp_addr.sin_addr.s_addr   = inet_addr("192.168.227.30");   //ANPRO_NET_TCU_MASTER
   }

   //_server_tcp_addr.sin_addr.s_addr   = inet_addr("192.168.10.171");
   _server_tcp_addr.sin_port          = htons(PROProjectInfo::IP_TCP_ServerPort);

   if (PROProjectInfo::IP_AddressMain) {
       _server_udp_addr.sin_addr.s_addr   = PROProjectInfo::IP_AddressMain + (PROProjectInfo::IP_AddressTCU_Master << 24);
   } else {
       _server_udp_addr.sin_addr.s_addr   = inet_addr("192.168.227.30");   //ANPRO_NET_TCU_MASTER
   }
   _server_udp_addr.sin_port          = htons(PROProjectInfo::IP_UDP_NetPort);

}

void
Anpro_Net::stop(void)
{
   if(_anpro_net_thread == NULL)
   {
	  return;
   }
   _exit_flag = true;
   Sleep(5000);
   closesocket(_pipes[1]);
	WaitForSingleObject(_anpro_net_thread, 5000/*INFINITE*/);
   closesocket(_pipes[0]);
   CloseHandle(_anpro_net_thread);
   _anpro_net_thread = NULL;

   delete _normal_Q;
   delete _urgent_Q;
}

/////////////////////////////////////////////////////////////////////////
//
// thread init/deinit
//
/////////////////////////////////////////////////////////////////////////
void
Anpro_Net::anpro_thread_init(void)
{
   _tcp_sock   = INVALID_SOCKET;
   _udp_sock   = INVALID_SOCKET;
   _exit_flag  = false;

   init_anpro_tcp();
   init_anpro_udp();
}

void
Anpro_Net::anpro_thread_deinit(void)
{
   if(_tcp_sock != INVALID_SOCKET)
   {
      ::closesocket(_tcp_sock);
   }

   if(_udp_sock != INVALID_SOCKET)
   {
      ::closesocket(_udp_sock);
   }
}

/////////////////////////////////////////////////////////////////////////
//
// support utilities
//
/////////////////////////////////////////////////////////////////////////
void
Anpro_Net::init_anpro_tcp(void)
{
   if(_tcp_sock != INVALID_SOCKET)
   {
      closesocket(_tcp_sock);
   }

   _tcp_sock   = init_client_socket();
   put_socket_nonblocking(_tcp_sock);

   _tcp_state  = TCP_State_NotConnected;
}

void
Anpro_Net::init_anpro_udp(void)
{
   if(_udp_sock != INVALID_SOCKET)
   {
      ::closesocket(_udp_sock);
   }
   _udp_sock   = init_udp_socket(PROProjectInfo::IP_UDP_NetPort);
}

void
Anpro_Net::try_connect_to_server(void)
{
   ::connect(_tcp_sock, (struct sockaddr*)&_server_tcp_addr, sizeof(_server_tcp_addr));

   _tcp_state = TCP_State_Connecting;

   _tcp_connect_timer.Start();
}

void
Anpro_Net::notify_anpro_thread(unsigned char event)
{
   ::send(_pipes[1], (const char*)&event, 1, 0);
}

unsigned char
Anpro_Net::read_notify_event(void)
{
   int   ret;
   unsigned char cmd;

   ret = ::recv(_pipes[0], (char*)&cmd, 1, 0);
   if(ret <= 0)
   {
      return Anpro_Net_Event_Quit_Message;
   }
   return cmd;
}

void
Anpro_Net::anpro_select_add_set(fd_set* set, int fd, int* maxfd)
{
   FD_SET((SOCKET)fd, set);

   if(*maxfd < fd)
   {
      *maxfd = fd;
   }
}

void
Anpro_Net::anpro_thread_pre_select(fd_set* rset, fd_set* wset, int* maxfd)
{
   *maxfd = 0;

   FD_ZERO(rset);
   FD_ZERO(wset);

   anpro_select_add_set(rset, _pipes[0], maxfd);
   anpro_select_add_set(rset, _udp_sock, maxfd);

   switch(_tcp_state)
   {
   case TCP_State_NotConnected:
      try_connect_to_server();
      anpro_select_add_set(wset, _tcp_sock, maxfd);
      break;

   case TCP_State_Connecting:
      anpro_select_add_set(wset, _tcp_sock, maxfd);
      break;

   case TCP_State_Connected:
      anpro_select_add_set(rset, _tcp_sock, maxfd);
      break;

   case TCP_State_ReconnWait:
      // nothing to do. just wait till timeout
      break;
   }
}

void
Anpro_Net::anpro_thread_post_select(fd_set* rset, fd_set* wset)
{
   if(FD_ISSET(_pipes[0], rset))
   {
      OnControlRX();
   }

   if(FD_ISSET(_udp_sock, rset))
   {
      OnUDPRX();
   }

   switch(_tcp_state)
   {
   case TCP_State_NotConnected:
      // XXX bug if we hit this case
      break;

   case TCP_State_Connecting:
      if(FD_ISSET(_tcp_sock, wset))
      {
         int   err,
               optlen = sizeof(err);

         getsockopt(_tcp_sock, SOL_SOCKET, SO_ERROR, (char*)&err, &optlen);
         if(err == 0)
         {
            OnTCPConnected();
         }
         else
         {
            _tcp_connect_timer.Stop();
            OnTCPDisconnected();
         }
      }
      break;

   case TCP_State_Connected:
      if(FD_ISSET(_tcp_sock, rset))
      {
         OnTCPRX();
      }
      break;

   case TCP_State_ReconnWait:
      // nothing to do. just wait till timeout
      break;
   }
}

void 
Anpro_Net::anpro_thread_check_timer(void)
{
   if(_exit_flag)
   {
      return;
   }

   if(_tcp_connect_timer.IsActive() && _tcp_connect_timer.GetTicks() >= 5000)
   {
      _tcp_connect_timer.Stop();
      OnTCPDisconnected();
   }

   if(_tcp_reconn_wait_timer.IsActive() && _tcp_reconn_wait_timer.GetTicks() >= 2000)
   {
      _tcp_reconn_wait_timer.Stop();
      init_anpro_tcp();
   }

   if(_net_check_timer.IsActive() && _net_check_timer.GetTicks() >= 10000)
   {
     // just do this for faster TCP reconnect
     OnTCPDisconnected();
   }
}

/////////////////////////////////////////////////////////////////////////
//
// message encoding
//
/////////////////////////////////////////////////////////////////////////
int
Anpro_Net::anpro_encode_message(bool is_urgent, unsigned char* msg, int size, unsigned char* buffer)
{
   unsigned char* pkt_pos;
   QueueANPRO10_CommandHeading*  UCmd = (QueueANPRO10_CommandHeading*)msg;
   QueueANPRO10_CommandHeading*  NCmd = (QueueANPRO10_CommandHeading*)msg;

   pkt_pos  = buffer;
   pkt_pos += ANPRO10_AddPacketPreAmble(pkt_pos);

   pkt_pos += is_urgent ? ANPRO10_AddPacketHeading(pkt_pos, UCmd->TxInfo.rxAddr, UCmd->TxInfo.rxId) :
                          ANPRO10_AddPacketHeading(pkt_pos, NCmd->TxInfo.rxAddr, NCmd->TxInfo.rxId);

   pkt_pos += is_urgent ? ANPRO10_AddCommand(pkt_pos, (unsigned char*)&UCmd->Data) :
                          ANPRO10_AddCommand(pkt_pos, (unsigned char*)&NCmd->Data);

   pkt_pos += ANPRO10_AddPacketTail(buffer, (pkt_pos - buffer), false);
   return (int)(pkt_pos - buffer);
}

/////////////////////////////////////////////////////////////////////////
//
// tx
//
/////////////////////////////////////////////////////////////////////////
void
Anpro_Net::tx_over_tcp(char* pkt, int pkt_len)
{
   int            nsent = 0,
                  ret;
   SimpleTimer    tx_timer;

   //
   // ugly but simple mechanism to prevent long tx hang due to
   // network error or whatever
   //
   tx_timer.Start();

   while(nsent < pkt_len)
   {
      ret = ::send(_tcp_sock, &pkt[nsent], pkt_len - nsent, 0);
      if(ret == SOCKET_ERROR)
      {
         if(WSAGetLastError() != WSAEWOULDBLOCK)
         {
            OnTCPDisconnected();
            return;
         }

         //
         // 10 sec might be way too high but who cares?
         //
         if(tx_timer.GetTicks() >= 10000)
         {
           OnTCPDisconnected();
           return;
         }
      }
      nsent += ret;
   }
}

void
Anpro_Net::tx_over_udp(char* pkt, int pkt_len)
{
   int ret;

   // destination is always master TCU
   ret = ::sendto(_udp_sock, pkt, pkt_len, 0,
            (struct sockaddr*)&_server_udp_addr, sizeof(_server_udp_addr));
   if(ret == SOCKET_ERROR)
   {
      init_anpro_udp();
   }
}

/////////////////////////////////////////////////////////////////////////
//
// event handlers
//
/////////////////////////////////////////////////////////////////////////
void
Anpro_Net::OnControlRX(void)
{
   //
   // this is actually just a FIF in reality.
   // but we don't need strict priority policy
   // with PC
   // -hkim-
   //
   switch(read_notify_event())
   {
   case Anpro_Net_Event_Normal_Message:
      OnNormalTXReq();
      break;

   case Anpro_Net_Event_Urgent_Message:
      OnUrgentTXReq();
      break;

   case Anpro_Net_Event_Quit_Message:
	  _exit_flag = true;
      break;
   }
}

void
Anpro_Net::OnUDPRX(void)
{
   char                 buffer[1024];
   struct sockaddr_in   from;
   int                  ret,
                        from_len;

   from_len = sizeof(from);
   ret = ::recvfrom(_udp_sock, buffer, 1024, 0, (struct sockaddr*)&from, &from_len);
   if(ret <= 0)
   {
      // just reinitialize
      init_anpro_udp();
      return;
   }
   
   _net_check_timer.Reset();

   OnNormalRX(buffer, ret);
}

void
Anpro_Net::OnTCPRX(void)
{
   unsigned char     buffer[1024];
   int               ret;

   ret = ::recv(_tcp_sock, (char*)buffer, 1024, 0);
   if(ret <= 0)
   {
      OnTCPDisconnected();
      return;
   }

   _tcp_reader.feed(buffer, ret);
}

void
Anpro_Net::OnTCPConnected(void)
{
   // get local ip address and use it as CurrentDeviceAddress
   //
   {
      struct sockaddr_in    myname;
      int                   myname_size = sizeof(myname);

      if(getsockname(_tcp_sock, (struct sockaddr*)&myname, &myname_size) == 0)
      {
         unsigned int  addr = ntohl(myname.sin_addr.s_addr);
         unsigned char last = (unsigned char)(addr & 0xff);

         extern short CurrentDeviceAddress;
         CurrentDeviceAddress = (last - ANPRO_NET_PC_START);
      }
   }
   _tcp_connect_timer.Stop();
   _tcp_state = TCP_State_Connected;
   _tcp_reader.reset();

   _net_check_timer.Start();
}

void
Anpro_Net::OnTCPDisconnected(void)
{
   closesocket(_tcp_sock);
   _tcp_state = TCP_State_ReconnWait;
   _tcp_reconn_wait_timer.Start();

   _net_check_timer.Stop();
}

void
Anpro_Net::OnNormalTXReq(void)
{
   int  size;
   int  pkt_len;

   if(_normal_Q->GetMessageCond(_q_msg_buf, &size) == 0)
   {
      return;
   }

   pkt_len = anpro_encode_message(false, (unsigned char*)_q_msg_buf, size, (unsigned char*)_bounce_buffer);

   tx_over_udp(&_bounce_buffer[ANPRO10_PREAMBLE_SIZE], pkt_len - ANPRO10_PREAMBLE_SIZE);
}

void
Anpro_Net::OnUrgentTXReq(void)
{
   int  size;
   int  pkt_len;

   if(_urgent_Q->GetMessageCond(_q_msg_buf, &size) == 0)
   {
      return;
   }

   if(_tcp_state != TCP_State_Connected)
   {
      return;
   }

   pkt_len = anpro_encode_message(true, (unsigned char*)_q_msg_buf, size, (unsigned char*)_bounce_buffer);

   tx_over_tcp(&_bounce_buffer[ANPRO10_PREAMBLE_SIZE], pkt_len - ANPRO10_PREAMBLE_SIZE);
}

void
Anpro_Net::OnNormalRX(char* msg, int len)
{
   if ( !_exit_flag ) ANPRO10_UDP_Receive((U8*)msg);
}

void
Anpro_Net::OnUrgentRX(char* msg, int len)
{
   ANPRO10_UDP_Receive((U8*)msg);
}

int
Anpro_Net::anpro_tcp_read_callback(Anpro10_Reader* reader, unsigned char* msg, int len, void* cb_arg)
{
   Anpro_Net* apnet = (Anpro_Net*)cb_arg;

   apnet->OnUrgentRX((char*)msg, len);
   return 0;
}

/////////////////////////////////////////////////////////////////////////
//
// main task
//
/////////////////////////////////////////////////////////////////////////

DWORD WINAPI
Anpro_Net::anpro_net_thread(LPVOID lpParameter)
{
   apnet = (Anpro_Net*)lpParameter;
   int               max_fd,
                     ret;
   fd_set            rset, wset;
   struct timeval    tv;

   apnet->anpro_thread_init();

   while(!_exit_flag)
   {
	  tv.tv_sec   = 1;
      tv.tv_usec  = 0;

      apnet->anpro_thread_pre_select(&rset, &wset, &max_fd);

      ret = ::select(max_fd + 1, &rset, &wset, NULL, &tv);
	  if(ret > 0)
      {
		 apnet->anpro_thread_post_select(&rset, &wset);
	  }

      apnet->anpro_thread_check_timer();
   }

   apnet->anpro_thread_deinit();
   return NULL;
}


