#pragma once

#include <ptcl_codec/ptcl_packet.h>

namespace ptcl_utility { namespace ansi_c12 { namespace dot18 {
	class FrameHead_CT;
}}}

class PTCL_CODEC_EXPORT ptcl_packet_ansi : public ptcl_packet
{
public:
	ptcl_packet_ansi(void) ;
	virtual ~ptcl_packet_ansi(void) ;

	virtual void reset();

	//��װ���ģ�������set_packet_buffer
	virtual void format_packet();
	unsigned char* GetDataPtr(void);

	//�������� ������set_packet_buffer
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_packet();
	virtual int parse_packet_suhe();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header(unsigned char *buffer,int len_buffer);
	virtual int parse_header_suhe(unsigned char *buffer,int len_buffer);

	//�����ն��߼���ַ ���ձ���˳��
	virtual unsigned int get_device_addr() { return 0; }; // ����Ҫʵ��

	//���ر������к�
	virtual int get_frame_seq();
	void set_frame_seq(int seq);

	//����CRCУ��ֵ
	unsigned short int get_check_sum_ansi(unsigned char *buffer,int len_buffer);

	//������վID
	virtual unsigned char get_host_id() { return 0; }; // ����Ҫʵ��

	unsigned char get_ctrl_code_area();
	void set_ctrl_code_area(unsigned char ctrl);

	unsigned char get_repeat_flag();
	void set_repeat_flag(unsigned char flag);

	unsigned char get_mult_first();
	void set_mult_first(unsigned char first);

	unsigned char get_mult_flag();
	void set_mult_flag(unsigned char flag);

	unsigned char get_afn();
	void set_afn(unsigned char afn); 


protected:
	//����ͷ�ṹ��
#pragma pack(push, 1)
	struct frame_header_struct
	{
		unsigned char frame_start;//0XEE
		unsigned char frame_fill;
		union 
		{
			struct
			{
				unsigned char	ctrl_fill		: 5 ,//D0--D4Ԥ��
								repeat_flag		: 1 ,//֡����λ�����ڷ�ֹ���鱻�ظ����ա�ÿ�������·���ʱ����λȡ�����������ط��ķ��飬��λ״̬���䡣
								mult_first		: 1 ,//1-��ʾ�÷����Ƕ���鴫��ĵ�һ������  
								mult_flag		: 1 ;//1:��ʾ�÷����Ƕ���鴫���һ���� 
			};
			unsigned char ctrl_code_area;
		};
		unsigned char frame_seq;
		unsigned short int len_data_area;  
		unsigned char afn;
	};
#pragma pack(pop)

	frame_header_struct *frame_header_;
};