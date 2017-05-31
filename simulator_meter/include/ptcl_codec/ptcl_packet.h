#pragma once

#include "ptcl_codec_global.h"

class PTCL_CODEC_EXPORT ptcl_packet
{
public:
	ptcl_packet(void);
	virtual ~ptcl_packet(void);

	virtual void reset() = 0;

	//��װ���ģ�������set_packet_buffer
	virtual void format_packet() = 0;

	//�������� ������set_packet_buffer
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_packet() = 0;
	
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header() = 0;

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header(unsigned char *buffer,int len_buffer) = 0;

	//�����ն��߼���ַ ���ձ���˳��
	virtual unsigned int get_device_addr() = 0;

	//���ر������к�
	virtual int get_frame_seq() = 0;

	//������վID
	virtual unsigned char get_host_id() = 0;

	//���ñ���buffer
	void set_packet_buffer(unsigned char *buffer,int len);

	//�����û�������buffer
	void set_data_area_buffer(unsigned char *buffer,int len);

	//�õ�����buffer
	unsigned char *get_packet_buffer();

	//�õ����ĳ���
	int get_packet_length();

	//�õ��û�������buffer
	unsigned char *get_data_area_buffer();

	//�õ��û������ݳ���
	int get_data_area_length();

	//���ر���ͷ����
	int get_header_len();

	enum { MAX_PACKET_LENGTH = 1536 };
protected:

	unsigned char get_check_sum(unsigned char *buffer,int len);

	unsigned char buf_packet_[MAX_PACKET_LENGTH];
	unsigned char *buf_data_area_;
	int len_packet_;
	int len_data_area_;
	int len_header_;
};
