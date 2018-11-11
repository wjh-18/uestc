#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>

using namespace std;

int main()
{
	int fd = open("a.c", O_RDWR | O_APPEND);//open the test file
	if( fd == -1 )
	{
		cout << "open error." << endl;
		return -1;
	}//return if open file error

	off_t CurrentPosition = lseek(fd, 0, SEEK_CUR);//get the seek after file opened
	if(CurrentPosition == -1 )
	{
		//get seek fail
		cout << "lseek error." << endl;
		close(fd);
		return 0;
	}
	cout << "The seek after opened is " << CurrentPosition << endl;
	if(lseek(fd, 6, SEEK_SET) == -1)
	{
		cout << "lseek error" << endl;
		close(fd);
		return 0;
	}//set the seek to 6 and return if error
	off_t NewCurrentPosition = lseek(fd, 0, SEEK_CUR);//get the seek after set get the answer of question 1
	if(NewCurrentPosition == -1 )
	{
		cout << "lseek error" << endl;
                close(fd);
                return 0;
	}//check if success
	cout << "The seek after set to 6 is " << NewCurrentPosition << endl;
		
	char buf[5];//define an array to save the word read from the file
	if(read(fd, &buf, 5) == -1)
	{
		//read file failed
		cout << "read file failed." << endl;
		close(fd);
		return 0;
	}
	
	cout << "Read 5 words after seek seted in file is " << buf << endl << "And the lseek is " << lseek(fd, 0, SEEK_CUR) << "." << endl;
	close(fd);
	return 0 ;
}
