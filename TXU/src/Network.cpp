#if (NETWORK==1)
/**
 * @file  cs8900if.c
 * @brief Ethernet network driver for CS8900A
 */
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>     // Must include to avoid trouble with include of RTOS.h in Sys_arch.h

    #include "lwip/opt.h"
    #include "anpro_net.h"

    #include "RTOS.h"
    #include "2410addr.h"
    #include "2410lib.h"

    #include "netif/cs8900if.h"
    #include "netif/etharp.h"
    #include "lwip/init.h"

    #include "lwip/tcp_impl.h"
    #include "lwip/udp.h"
    #include "lwip/tcpip.h"
    #include "lwip/api.h"

    #include "rtos.h"
    #include "TSNConstants.h"

    #include "app/tftp_server.h"
    #include "app/shell.h"

extern bool Master;

extern void ANWin_UDP_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *addr, u16_t port);
//OS_STACKPTR int SendUDPTaskStack[256];
//OS_TASK SendUDPTaskHandle;  /* Task control blocks */
void SendUDPTask(void);
void SendBasicTFTPServerTask(void);

    #ifdef __cplusplus
extern "C"
{
    #endif

static void start_tftp_server(void);

struct netif eth0;
OS_STACKPTR int CS8900Stack[1024];
OS_TASK *HandleCS8900 = (OS_TASK *)NULL;  // Task control blocks

void tcpip_init_done_ok(void *arg) {
    sys_sem_t *sem;
    sem = (sys_sem_t *)arg;
    sys_sem_signal(sem);
}

static void start_network_app_tasks(void) {
    shell_init();
    start_tftp_server();
    start_anpro_net();
}

void CS8900ATask(void) {
    extern void cs8900_deplete_event_queue(void);
    struct cs8900if *cs8900if = (struct cs8900if *)eth0.state;

    cs8900_deplete_event_queue();

    // hkim mod.
    while ( 1 ) {
        if ( OS_WaitEventTimed(NETWORK_IRQ_SIGNAL, 1000) != 0 ) {
            cs8900if->interrupts++;
            cs8900if_service(&eth0);
        }
        // FIXME -hkim-
        // check link status
    }
}

void StartNetDriverTask(void) {
    OS_IncDI();
    HandleCS8900 = new OS_TASK();
    OS_CREATETASK(HandleCS8900, "CS8900A", CS8900ATask, DEFAULT_THREAD_PRIO, CS8900Stack);
    OS_DecRI();
}

void StartNetwork(void) {
    sys_sem_t sem;
    ip_addr_t ipaddr, netmask, gw;

    if ( sys_sem_new(&sem, 0) ==  ERR_OK ) {
        tcpip_init(tcpip_init_done_ok, &sem);
        sys_sem_wait(&sem);
        sys_sem_free(&sem);
    }

    setup_anpro_network_address(&eth0, &netmask, &gw, &ipaddr);

    netif_add(&eth0, &ipaddr, &netmask, &gw, NULL, cs8900if_init, tcpip_input);
    netif_set_default(&eth0);
    netif_set_up(&eth0);
#if 0
    {
        static struct udp_pcb *ANWin_pcb = udp_new();
        // initialize DNS client
        udp_bind(ANWin_pcb, IP_ADDR_ANY, 550);
        udp_recv(ANWin_pcb, ANWin_UDP_recv, NULL);
    }
#endif
    //OS_CREATETASK(&SendUDPTaskHandle  , "Send UDP", SendUDPTask   , 50, SendUDPTaskStack);
    //OS_CREATETASK(&SendUDPTaskHandle  , "BasicTFTPServer", SendBasicTFTPServerTask   , 50, SendUDPTaskStack);
    start_network_app_tasks();

}

#ifdef __cplusplus
}
#endif

    #if 0
/**
 * Receive input function for DNS response packets arriving for the dns UDP pcb.
 *
 * @params see udp.h
 */
void
ANWin_UDP_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, ip_addr_t *addr, u16_t port){
    char tmpStr[100];
    memset(tmpStr,0,100);
    memcpy(tmpStr,p->payload,p->len);
    pbuf_free(p);

    return;
}
void SendUDPTask(void){
    OS_Delay(1000);
    static struct udp_pcb *ANWin_pcb = udp_new();
    char msg[100];
    int Cnt = 0;

    //netconn_connect(struct netconn *conn, ip_addr_t *addr, u16_t port)
    struct netconn *conn;
    ip_addr_t addr;
    //int ErrStat = netconn_connect(conn,&addr,502);
    //(void) pvParameters; // Satisfy complier
    //struct netconn *conn;
    struct netbuf *inbuf;
    char *rq;
    int length;

// Create a new socket
    conn = netconn_new(NETCONN_TCP);
// Bind connection
    ip_addr_t TCPaddr;
    IP4_ADDR(&TCPaddr, 192,168,227,106);

    while ( true ) {
        netconn_bind(conn,&TCPaddr,550);
        if ( conn != NULL ) {
// Just read page and throw away
            int ErrConn = netconn_recv(conn,&inbuf);
            if ( inbuf != NULL ) {
                void *Myrq;
                u16_t Length;
                netbuf_data(inbuf,&Myrq,&Length);
                netbuf_delete(inbuf);
            } else {
                OS_Delay(1000);
            }
            //netconn_delete(newconn);
        }
    }
    /*
    while ( true ) {
        OS_Delay(2000);
        sprintf(msg,"Dette er test nummer %i",Cnt++);
        struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT,strlen(msg),PBUF_RAM);
        memcpy (p->payload, msg, strlen(msg));
        udp_sendto(ANWin_pcb, p, IP_ADDR_BROADCAST, 501); //dest port
        pbuf_free(p);
    }
  */

}

static void EchoRequest( struct netconn *pxNetCon ){
    struct netbuf *pxRxBuffer=(struct netbuf*)NULL;
    char *pcRxString = (char*)NULL;
    u16_t usLength;

    if ( netconn_recv( pxNetCon,&pxRxBuffer ) == ERR_OK ){
        netbuf_data( pxRxBuffer, ( void ** ) &pcRxString, &usLength );
        if (  pcRxString != NULL){
            netconn_write( pxNetCon, pcRxString, (u16_t) usLength, NETCONN_COPY );
        }
        netbuf_delete( pxRxBuffer );
    }
}

void SendBasicTFTPServerTask(void){
    struct netconn *pxTCPListener=(struct netconn*)NULL, *pxNewConnection=(struct netconn*)NULL;
    pxTCPListener = netconn_new( NETCONN_TCP );

    netconn_bind(pxTCPListener, NULL, 23 );
    netconn_listen( pxTCPListener );

    for(;
        ;
        ){
        if(netconn_accept(pxTCPListener,&pxNewConnection) == ERR_OK){
            EchoRequest(pxNewConnection);
        } else {
            OS_Delay(100);
        }
    }
}
    #endif

    #ifdef __cplusplus
extern "C"
{
    #endif

/////////////////////////////////////////////////////////////////////////
// XXX
// be very careful with this code.
// this runs in lwip tcpip_thread context.
// so if you don't pay attention, you get all the concurrency issues
// as well as blocking lwip tcip_thread
/////////////////////////////////////////////////////////////////////////
static tTFTPError
tftp_get_request_handler(tTFTPConnection *psTFTP) {
    // GET reqiest, aka, clients want to read data from server
    // in this case, we just send a data filled with 0xff
    memset(psTFTP->pui8Data, 0xff, psTFTP->ui32DataLength);
    return TFTP_OK;
}

static tTFTPError
tftp_put_request_handler(tTFTPConnection *psTFTP) {
    // PUT request, aka, clients want to write data to server
    // in this case, we are just a data sink hole.
    return TFTP_OK;
}

static void
tftp_transfer_close(tTFTPConnection *psTFTP) {
    // nada
}

static tTFTPError
tftp_server_request_callback(tTFTPConnection *psTFTP, bool bGet, int8_t *pui8FileName, tTFTPMode eMode) {
    psTFTP->pfnGetData  = tftp_get_request_handler;
    psTFTP->pfnPutData  = tftp_put_request_handler;
    psTFTP->pfnClose    = tftp_transfer_close;

    if ( bGet ) {
        psTFTP->ui32DataRemaining = 1024 * 1024 * 10;   // 10MB data for test
    } else {
        // nada
    }
    return TFTP_OK;
}

static void
start_tftp_server(void) {
    TFTPServerInit(tftp_server_request_callback);
}

#ifdef __cplusplus
}
#endif

#endif //NETWORK==1

