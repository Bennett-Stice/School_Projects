/**
*@author Bennett Stice
*@date 9/2/2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <sys/wait.h> //for waited
#include <cstring>
#include "Command.hpp"
#include <cstdio>
#include <signal.h>

//Kinda a cheeky way of solving this problem but eh it works
int globalPid;
Command globalCom;
bool trigger;

void sigHandler(int signum)
{

    if (signum==SIGCHLD&&trigger)//&&trigger
    {
        cout<<"Completed: PID= "<<globalPid<<" : "<< globalCom<<endl;
        trigger=false;
    }
}

using namespace std;


int main (int argc, char *argv[])
{

    Command com;

    // prompt for and read in first command.
    cout << ">>>>> ";
    com.read();

    int pipeInfo[2];
    int status;

    int pipNum=-1;

    while (com.name()!="exit")
    {
        //change the directory
        if (com.name()=="cd")
        {
            chdir(com.args()[1].c_str());

            //read in the next command
            cout<<">>>>> ";
            com.read();
        }

        else
        {
            if (com.pipeOut())
            {
                status= pipe(pipeInfo);//create pip before the fork
            }

            //fork the processes
            int pid=fork();
            globalPid=pid;

            if (pid==0)//this is the child
            {

                //if there is an redirect in change the input to the file
                if(com.redirIn())
                {
                    FILE *fp=fopen(com.inputRedirectFile().c_str(),"r");
                    dup2(fileno(fp), fileno(stdin));
                    fclose(fp);
                }

                //if there is a redirect out change the output to the file
                if(com.redirOut())
                {
                    FILE *fp=fopen(com.outputRedirectFile().c_str(),"w");
                    dup2(fileno(fp), fileno(stdout));
                    fclose(fp);
                }

                //if the command has a pipe then change the output to the output of the pipe
                if (com.pipeOut())
                {
                    dup2(pipeInfo[1],fileno(stdout));
                    close(pipeInfo[0]);
                }

                //if the last command had a pipe change the output of the first pipe to the input of the second
                if (pipNum!=-1)
                {
                    dup2(pipNum,fileno(stdin));
                    close(pipeInfo[1]);
                    pipNum=-1;
                }


                //create args
                char* *args=new char*[com.numArgs()+1];

                for (int i=0;i<com.numArgs();i++)
                {
                    args[i]=new char[com.args()[i].length()+1];
                    strcpy(args[i],com.args()[i].c_str());
                }

                args[com.numArgs()]=NULL;


                execvp(args[0],args); //run args
            }
            if (pid!=0) //this is parent
            {

                close(pipeInfo[1]);

                //if it isn't backgrounded wait for child to finish
                if (!com.backgrounded())
                {
                    waitpid(0,NULL,0);
                }

                //if command is backgrounded return the PID of the child when it completes
                if (com.backgrounded())
                {
                    trigger=true;
                    globalCom=com;
                    signal(SIGCHLD,sigHandler);
                }

                //remember the output of the last pipe
                if (com.pipeOut())
                {
                    pipNum=pipeInfo[0];
                }


                //Read in next command
                else
                {
                    cout<<">>>>> ";
                }

                com.read();
            }
        }
    }

    cout<<"Thank you for using Stice Shell"<<endl;



    return 0;
}

