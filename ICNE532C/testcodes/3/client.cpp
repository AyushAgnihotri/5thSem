#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <pthread.h>
#include <string>
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

#include <dirent.h>
#include <errno.h>
#define BUF_SIZE 256
using namespace std;

int setup(int argc, char *argv[]);
void error(const char *msg);



vector <string> filelist;

void send_message(int sockfd, string msg)
{
    ssize_t n = send(sockfd, msg.c_str(), msg.length() + 1, 0);
    if (n < 0) {
        error("ERROR sending to socket");
    }
}

void send_file_list(string message)
{
    int clisockfd = atoi(message.substr(0,message.find(":")-1).c_str());
    string files = "List of files in current directory:\n";
    for (int i=0; i<filelist.size(); i++) {
        files = files + filelist[i] + "\n";
    send_message(clisockfd, files);
    }
}

void updateFile()
{
    DIR* FD;
    struct dirent* in_file;
    if (NULL == (FD = opendir ("./"))) 
	{
		fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        exit(0);
	}
    while ((in_file = readdir(FD))) 
	{
        if (in_file->d_type == DT_DIR)
            continue;
		if (!strcmp (in_file->d_name, "."))
			continue;
		if (!strcmp (in_file->d_name, ".."))    
			continue;
        filelist.push_back(in_file->d_name);
	}
}

void send_file_to_client(string message)
{
    int clisockfd = atoi(message.substr(0,message.find(":")-1).c_str())+1;
    string filename = message.substr(message.find(":")+1,string::npos);
    if (find(filelist.begin(), filelist.end(), filename) == filelist.end()) {
        send_message(clisockfd, "No such file - " + filename + " on sever directory!\n");
    } else {
        char f[filename.size()];
        for (int i=0; i<filename.size(); i++)
            f[i] = filename[i];
        f[filename.size()] = '\0';
        cout << f << endl;
        FILE *fp = fopen(f,"rb");
        if(fp==NULL)
        {
            send_message(clisockfd, "File open error");
            return ;
        }
        for (int i=0;;i++)
        {
            /* First read file in chunks of BUF_SIZE bytes */
            unsigned char buff[BUF_SIZE+2]={0};
            int nread = fread(buff,1,BUF_SIZE,fp);
            printf("Bytes read %d \n", nread);

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(clisockfd, buff, nread);
            }

            /*
             * There is something tricky going on with read ..
             * Either there was error, or we reached end of file.
             */
            if (nread < BUF_SIZE)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }

    }
}

void error(const char *msg) 
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void *recv_message_from_server(void *sfd)
{
    int sockfd = *(int *)sfd;
    while (1) {
        char buffer[256];
        bzero(buffer, 256);
        ssize_t n = recv(sockfd, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            error("ERROR receiving from socket");
        }
        string message (buffer);
        if (message.find("list-files") != string::npos){
            send_file_list(message);
        } else if (message.find("get:") != string::npos){
            send_file_to_client(message);
        } else {
            write(fileno(stdout), "< ", 2);
            write(fileno(stdout), buffer, sizeof(buffer));
        }
    }
}

void *send_message_to_server(void *sfd)
{
    int sockfd = *(int *)sfd;
    while (1) {
        string buffer;
        getline(cin, buffer);
        ssize_t n = send(sockfd, buffer.c_str(), buffer.length(), 0);
        if (n < 0) {
            error("ERROR sending to socket");
        }
    }
}

string recv_message(int sockfd)
{
    char buffer[256];
    bzero(buffer, 256);
    ssize_t n = recv(sockfd, buffer, sizeof(buffer), 0);
    if (n <= 0) {
        error("ERROR receiving from socket");
    }
    return string(buffer);
}

int main(int argc, char *argv[])
{
    updateFile();
    int sockfd = setup(argc, argv);
    string greetmsg = recv_message(sockfd);
    cout << greetmsg << endl;
    string name;
    cin >> name;
    send_message(sockfd, name);

    pthread_t rid, sid;
    pthread_create(&rid, NULL, recv_message_from_server, (void *)&sockfd);
    pthread_create(&sid, NULL, send_message_to_server, (void *)&sockfd);

    pthread_join(rid, NULL);
    pthread_join(sid, NULL);

    close(sockfd);
    return 0;
}

int setup(int argc, char *argv[])
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3) {
        error("ERROR no hostname or port provided");
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    portno = atoi(argv[2]);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        error("ERROR no such host");
    }
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server -> h_addr, (char *) &serv_addr.sin_addr.s_addr, 
            server -> h_length);

    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on connecting");
    }
    return sockfd;
}

