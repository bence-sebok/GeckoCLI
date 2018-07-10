// standard library headers:
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h> // terminal, serial port
#include <errno.h> // perror
#include <time.h> // date, time
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

// serial communication settings:
#define UART_FRAME (CS8|CREAD|CLOCAL)
#define BAUDRATE B115200

// function prototypes
void settings_serial(int serial_fd);
void logDateTime(FILE * fd);
void welcomeText();

int main(int argc, char* argv[])
{
    // fd_set:
    fd_set file_fs;
    struct timeval timeout;
    struct termios original_settings;
    // serial device:
    int serial_fd;
    char * deviceName = "/dev/ttyACM0";
    int sorveg_jel = 0x0d;
    // input buffer
    char ch;
    char message[100];
    uint8_t msgSize = 0;
    // Log file:
    const char * filename = "log.txt";
    FILE * file_log = fopen(filename, "at");
    if(file_log == NULL)
    {
            perror("Cannot open file.\n");
            return 1;
    }
    // save previous terminal values
    tcgetattr( 0, &original_settings );

    // ****************************
    // serial device
    // ****************************
    // Handling device name
    if(argc < 2)
    {
            printf("Default device name is used: %s\n", deviceName);
    }
    else
    {
            deviceName = argv[1];
    }
    // Opnening serial device
    printf("Opening device: %s\n", deviceName);
    serial_fd = open("/dev/ttyACM0", O_RDWR);
    FILE * fp = fdopen(serial_fd, "rw");
    if(serial_fd == -1)
    {
            printf( "Failed to open port: %s\n", deviceName);
    }
    if(!isatty(serial_fd))
    {
            printf("%s device is NOT a tty device.\n", deviceName);
            tcsetattr( 0, TCSANOW, &original_settings );
            return 1;
    }
    settings_serial(serial_fd);
    // ****************************
    // synchronous I/O multiplexing
    // ****************************
    FD_ZERO(&file_fs);
    timeout.tv_sec = 5 * 60;
    timeout.tv_usec = 0;
    while(1)
    {
        // init fds and max_fd:
        FD_SET(STDIN_FILENO, &file_fs);
        FD_SET(serial_fd, &file_fs);
        int max_fd = serial_fd > STDIN_FILENO ? serial_fd : STDIN_FILENO;
        // checks for events:
        if(select(max_fd + 1, &file_fs, NULL, NULL, &timeout) < 0)
        {
            perror("Error on select(): ");
        }
        // changes for stdin? 
        if(FD_ISSET(STDIN_FILENO, &file_fs))
        {
            while ((ch = fgetc(stdin)) != '\n')
            {
                write(serial_fd, &ch, 1);
            }
            write(serial_fd, &sorveg_jel, 1);
        }
        // changes for serial device?
        if(FD_ISSET(serial_fd, &file_fs))
        {
            while ((ch = fgetc(fp)) != '\n')
            {
                write(STDOUT_FILENO, &ch, 1);
                // writing to message buffer
                message[msgSize] = ch;
                msgSize++;
            }
            putchar('\n');
            fflush(stdout);
            // closing message and set writing pos to zero
            message[msgSize] = '\0';
            msgSize = 0;
            // logging to text file
            logDateTime(file_log);
            fprintf(file_log, "%s\n", message);
	    }
    }
    close(serial_fd);
    return 0;
}

// Settings for serial device
void settings_serial(int serial_fd)
{
    struct termios tio; // local variable for settings
    memset(&tio,0,sizeof(tio)); // clearing the variable
    // setting flags:
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=UART_FRAME;
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;
    cfsetospeed(&tio,BAUDRATE);
    cfsetispeed(&tio,BAUDRATE);
    // setting attributes:
    tcsetattr(serial_fd,TCSANOW,&tio);
}

// Writing formatted date and time to fd file
// Line format: yyyy-mm-dd HH:MM::SS: RECEIVED MESSAGE
void logDateTime(FILE * fd)
{
        time_t pillanatnyilag;
        struct tm ido;
         // get current time
        pillanatnyilag = time(NULL);
        ido = *localtime(&pillanatnyilag);
        fprintf(fd, "%d-", ido.tm_year+1900);
        // month
        if(ido.tm_mon+1 < 10)
        {
                fprintf(fd, "0%d-", ido.tm_mon+1);
        }
        else
        {
                fprintf(fd, "%d-", ido.tm_mon+1);
        }
        // day
        if(ido.tm_mday < 10)
        {
                fprintf(fd, "0%d ", ido.tm_mday);
        }
        else
        {
                fprintf(fd, "%d ", ido.tm_mday);
        }
        // hour
        if(ido.tm_hour < 10)
        {
                fprintf(fd, "0%d:", ido.tm_hour);
        }
        else
        {
                fprintf(fd, "%d:", ido.tm_hour);
        }
        // minute
        if(ido.tm_min < 10)
        {
                fprintf(fd, "0%d:", ido.tm_min);
        }
        else
        {
                fprintf(fd, "%d:", ido.tm_min);
        }
        // second
        if(ido.tm_sec < 10)
        {
                fprintf(fd, "0%d: ", ido.tm_sec);
        }
        else
        {
                fprintf(fd, "%d: ", ido.tm_sec);
        }
}

void welcomeText()
{
	printf("PEP hazi feladat\n");
	printf("Seres Zsofia, Sebok Bence\n");
	printf("Baud rate: 115200 bit/s\n");
	printf("UART frame: 8N1\n");
}

// Settings for stdio
void settings_stdio()
{
    struct termios stdio;
    memset(&stdio,0,sizeof(stdio));
    stdio.c_iflag=0;
    stdio.c_oflag=0;
    stdio.c_cflag=0;
    stdio.c_lflag=0;
    stdio.c_cc[VMIN]=1;
    stdio.c_cc[VTIME]=0;
    tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
    tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}
