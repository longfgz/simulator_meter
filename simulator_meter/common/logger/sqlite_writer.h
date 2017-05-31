#pragma once
#include <logger/logger_global.h>
#include <sqlite/sqlite3.h>
#include "log_message.h"

class LOGGER_EXPORT sqlite_writer
{
public:
	sqlite_writer(void);
	~sqlite_writer(void);
	int test(void);
	int start(char * root_dir);
	void close();
	int join();
	int stop();
	void insert_message(log_message & message);

protected:
	enum packet_type
	{
		packet_type_recv		 = 1,
		packet_type_send		 = 2,
		packet_type_recv_error   = 3,
		packet_type_send_error   = 4,
	};
	sqlite3 * db_;
	boost::shared_ptr<boost::thread> thread_ptr_;
	int exit_;
	char root_dir_[512];
	char file_name_[512];
	boost::mutex mutex_;
	time_t tm_begin_;  //��ǰ��¼����һ��ĵ�1��
	int file_seq_;  //����ĵڼ����ļ�
	
	//���ƣ��������У�һ�����룬һ��д�⣬���д����Ǹ���ɣ����л�
	std::deque <log_message> d_message_1_;
	std::deque <log_message> d_message_2_;
	std::deque <log_message> * p_d_msg_insert_;
	std::deque <log_message> * p_d_msg_write_db_;
	volatile int cur_insert_d_msg_;

	bool msg_full_;  //deque

	void write_message();
	void clear_log();
	int open_db(time_t message_time);
	int run();
	bool check_dir(char *dir);
	int write_db( std::deque <log_message>& d_msg );
	void packet_to_string(	unsigned char dir_type,
							  unsigned char *buffer,short int buf_size,char *dst_buffer);
	
};

