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

map <string, int> nametable;
vector <string> filelist;

int setup(int argc, char *argv[]);
void send_list(int clisockfd);
void send_to_another_client(int clisockfd, string cliname, string message);
string ask_name(int clisockfd);
void send_file_list(int clisockfd);
void send_file_to_client(int clisockfd, string message);
void updateFile();

void error(const char *msg) 
{
    perror(msg);
    exit(EXIT_FAILURE);
}

string recv_message(int sockfd)
{
    char buffer[256];
    bzero(buffer, 256);
    ssize_t n = recv(sockfd, buffer, sizeof(buffer), 0);
    if (n <= 0) {
        cout << "ERROR receiving from socket" << endl;
        return "EOF";
    }
    string tempstr (buffer);
    return tempstr;
}

void send_message(int sockfd, string msg)
{
    ssize_t n = send(sockfd, msg.c_str(), msg.length() + 1, 0);
    if (n < 0) {
        error("ERROR sending to socket");
    }
}

void *handle_client(void *sfd)
{
    int clisockfd = *(int *)sfd;
    string cliname = ask_name(clisockfd);
    nametable[cliname] = clisockfd;

    while (1) {
        string message = recv_message(clisockfd);
        cout << cliname << ": " << message << endl;
        if (message == "EOF") {
            nametable.erase(cliname);
            break;
        } else if (message == "list-people") {
            send_list(clisockfd);
        } else if (message == "list-files"){
            send_file_list(clisockfd);
        } else if (message.find("get:") == 0){
            send_file_to_client(clisockfd, message);
        } else if (message.find(":") == string::npos) {
            send_message(clisockfd, "Invalid command\n");
        } else {
            send_to_another_client(clisockfd, cliname, message);
        }
    }
}



int main(int argc, char *argv[])
{
    updateFile();
    for (int i=0; i<filelist.size(); i++)
        cout << filelist[i] << endl;
    int sockfd = setup(argc, argv);
    struct sockaddr_in cli_addr;
    listen(sockfd, 5);
    socklen_t clilen = sizeof(cli_addr);

    while (1) {
        int clisockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (clisockfd < 0) {
            error("ERROR on accept");
        }
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, (void *)&clisockfd);
    }
    close(sockfd);
    return 0;
}

string ask_name(int clisockfd)
{
    send_message(clisockfd, "Connected, type list for the list of clients\nEnter your name");
    string cliname = recv_message(clisockfd);
    cout << cliname << " connected" << endl;
    return cliname;
}

void send_to_another_client(int clisockfd, string cliname, string message)
{
    string recvname = message.substr(0, message.find(":"));
    if (nametable.find(recvname) == nametable.end()) {
        send_message(clisockfd, "No such client\n");
    } else {
        int recvsockfd = nametable[recvname];
        

        int temp = clisockfd;
        char msg[100];
        char temp2[100];
        int k=0,k2=0;
        while(temp) {
            temp2[k++] = '0'+temp%10;
            temp/=10;
        }
        k--;
        while(k>=0) {
            msg[k2++] = temp2[k--];
        }
        msg[k2] = 0;
        string org_msg = string (msg) + ":" + message.substr(message.find(":") + 1, string::npos);
        send_message(recvsockfd, org_msg + "\n");
        // if (message.substr(message.find(":") + 1, string::npos).find("get:")){
        //     string m = recv_message(recvsockfd);
        //     send_message(clisockfd, m);

        // }
        // send_message(recvsockfd, org_msg + "\n");
    }
}

void send_file_to_client(int clisockfd, string message)
{
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



void send_list(int clisockfd)
{
    send_message(clisockfd, "List of clients:\n");
    for (map<string, int>::iterator it = nametable.begin(); it != nametable.end(); it++) {
        send_message(clisockfd, it -> first + "\n");
    }
}

void send_file_list(int clisockfd)
{
    send_message(clisockfd, "List of files in current directory:\n");
    string files = "";
    for (int i=0; i<filelist.size(); i++) {
        files = files + filelist[i] + "\n";
    send_message(clisockfd, files);
    }
}

int setup(int argc, char *argv[])
{
    signal(SIGCHLD, SIG_IGN);
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    if (argc < 2) {
        error("ERROR no port provided");
    }
    cout << "Server running on port " << argv[1] << endl;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
    }
    return sockfd;
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