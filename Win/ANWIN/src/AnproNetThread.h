/////////////////////////////////////////////////////////////////////////
//
// ANPRO10 over Network
//
// Revision History
// - 2016/Aug/18 initial release by hkim
//
/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------

#ifndef AnproNetThreadH
#define AnproNetThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <ctime>
#include "Winsock2.h"

using namespace std;

#include "TSNMessageQ.h"
#define ANPRO_NET_GATEWAY               1
#define ANPRO_NET_TCU_MASTER            30
#define ANPRO_NET_TCU_MASTER_END        49  // Not in use
#define ANPRO_NET_TCU_SLAVE_START       50
#define ANPRO_NET_TCU_SLAVE_END         69
#define ANPRO_NET_PC_START              80
#define ANPRO_NET_PC_END                149
#define ANPRO_NET_TDU_START             150
#define ANPRO_NET_TDU_END               199


/////////////////////////////////////////////////////////////////////////
//
// real simple timer class
// I just hated porting SGTimer here
//
/////////////////////////////////////////////////////////////////////////
class SimpleTimer
{
   clock_t startedAt;
	clock_t pausedAt;
	bool started;
	bool paused;
public:
	SimpleTimer();
	bool IsStarted();
	bool IsStopped();
	bool IsPaused();
	bool IsActive();
	void Pause();
	void Resume();
	void Stop();
	void Start();
	void Reset();
	clock_t GetTicks();
};

/////////////////////////////////////////////////////////////////////////
//
// ANPRO10 Message reader
//
/////////////////////////////////////////////////////////////////////////
#define ANPRO_READER_BUFFER_SIZE        (8096 * 2)

class Anpro10_Reader;
typedef int (*anpro10_reader_callback)(Anpro10_Reader* reader, unsigned char* anpro10_msg, int len, void* cb_arg);

class Anpro10_Reader
{
public:
   Anpro10_Reader(anpro10_reader_callback cb, void* cb_arg);
   void feed(const unsigned char* msg, int len);
   inline void reset(void);
private:
   inline void decode(unsigned char in);
   inline unsigned char calc_csum(const unsigned char* msg, int len);

   enum
   {
      ANPRO10_RX_Header,
      ANPRO10_RX_Body,
   } state;

   unsigned char     bounce_buffer[ANPRO_READER_BUFFER_SIZE];
   unsigned int      buffered_data_len;
   unsigned int      body_len_to_read;
   anpro10_reader_callback    callback;
   void*                      cb_arg;
};

/////////////////////////////////////////////////////////////////////////
//
// the bad guy
//
/////////////////////////////////////////////////////////////////////////
class Anpro_Net
{
public:
   Anpro_Net();
   virtual ~Anpro_Net();

protected:

};


//---------------------------------------------------------------------------
class AnproNetThread : public TThread
{
protected:
	void __fastcall Execute();
	virtual void OnControlRX(void);

	virtual void OnUDPRX(void);

	virtual void OnTCPConnected(void);
	virtual void OnTCPDisconnected(void);
	virtual void OnTCPRX(void);

	virtual void OnNormalTXReq(void);
	virtual void OnUrgentTXReq(void);

	virtual void OnNormalRX(char* msg, int len);
	virtual void OnUrgentRX(char* msg, int len);

private:
   static DWORD WINAPI anpro_net_thread(LPVOID lpParameter);
   void notify_anpro_thread(unsigned char event);
   unsigned char read_notify_event(void);

   void anpro_thread_init(void);
   void anpro_thread_deinit(void);

   void init_anpro_tcp(void);
   void init_anpro_udp(void);
   void try_connect_to_server(void);

   void anpro_thread_pre_select(fd_set* rset, fd_set* wset, int* maxfd);
   void anpro_thread_post_select(fd_set* rset, fd_set* wset);
   void anpro_thread_check_timer(void);
   void anpro_select_add_set(fd_set* set, int fd, int* maxfd);

   int anpro_encode_message(bool is_urgent, unsigned char* msg, int size, unsigned char* buffer);

   static int anpro_tcp_read_callback(Anpro10_Reader* reader, unsigned char* msg, int len, void* cb_arg);

   void tx_over_tcp(char* pkt, int pkt_len);
   void tx_over_udp(char* pkt, int pkt_len);

   TSNMessageQ*   _normal_Q;
   TSNMessageQ*   _urgent_Q;
   HANDLE         _anpro_net_thread;
   int            _pipes[2];
   bool           _exit_flag;

   SOCKET         _tcp_sock;
   SOCKET         _udp_sock;

   struct sockaddr_in   _server_tcp_addr;
   struct sockaddr_in   _server_udp_addr;

   volatile enum {
	  TCP_State_NotConnected,
	  TCP_State_Connecting,
	  TCP_State_Connected,
	  TCP_State_ReconnWait,
   } _tcp_state;

   Anpro10_Reader    _tcp_reader;

   SimpleTimer       _tcp_reconn_wait_timer;
   SimpleTimer       _tcp_connect_timer;
   SimpleTimer       _net_check_timer;

   char              _bounce_buffer[ANPRO_READER_BUFFER_SIZE];
   char              _q_msg_buf[ANPRO_READER_BUFFER_SIZE];
public:
	__fastcall AnproNetThread(bool CreateSuspended);
   void __fastcall send_normal(char* msg, int size);
   void __fastcall send_urgent(char* msg, int size);
   void __fastcall start(void);
   void __fastcall stop(void);
};
//---------------------------------------------------------------------------
#endif
