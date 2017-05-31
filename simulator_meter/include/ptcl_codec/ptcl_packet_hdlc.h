#pragma once

#include <ptcl_codec/ptcl_packet.h>

class PTCL_CODEC_EXPORT ptcl_packet_hdlc : public ptcl_packet
{
public:
	ptcl_packet_hdlc(int packet_type = 1);
	virtual ~ptcl_packet_hdlc(void);

	virtual void reset();

	//��װ���ģ�������set_packet_buffer
	virtual void format_packet();

	//�������� ������set_packet_buffer
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_packet();
	
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header(unsigned char *buffer,int len_buffer);

	//�����ն��߼���ַ ���ձ���˳��
	virtual unsigned int get_device_addr();

	//���ر������к�
	virtual int get_frame_seq();

	//������վID
	virtual unsigned char get_host_id();

	//�߼���ַ
	void set_device_addr(unsigned short dev_addr);

	//��վ��ַ
	void set_host_id(unsigned char id);

	//֡���
	void set_frame_seq(unsigned char seq);


	unsigned char get_ctrl_code_area();
	void set_ctrl_code_area(unsigned char code);
	
	unsigned char get_cca_recv_seq();
	void set_cca_recv_seq(unsigned char seq);
	
	unsigned char get_cca_pf();
	void set_cca_pf(unsigned char pf);
	
	unsigned char get_cca_send_seq();
	void set_cca_send_seq(unsigned char seq);
	
	unsigned char get_cca_end();
	void set_cca_end(unsigned char end);

protected:
	//����ͷ�ṹ��
#pragma pack(push, 1)
	struct frame_header_struct
	{
		unsigned char frame_start;//0x7E
		/*union 
		{
			struct
			{
				unsigned short int    len_frame	    :	 11 ,//D0--D10���ȣ�����ͷ��ǣ�β��ǣ�
									  fta_separator	:	 1 ,//D11 �ֶα��
									  frame_type	:	 4 ;//D12--D15 ����ʽ1010:��ʽ3
			};//��Ҫת�������ֽ���
			unsigned short int frame_type_area;  
		};*/
		unsigned short int frame_type_area;  
		union 
		{
			struct
			{
				unsigned char	device_addr_dst[4];
				unsigned char   host_id_src;
			};
			struct
			{
				unsigned char	host_id_dst;	
				unsigned char	device_addr_src[4];
			};
		};
		union 
		{
			struct
			{
				unsigned char cca_end	 	:	 1 ,//D7 Iʱ��0 ����ʱ��1
							  cca_send_seq	:	 3 ,//D4--D6 �������
							  cca_pf		:	 1 ,//D3 ��ѯ/����λ
							  cca_recv_seq	:	 3 ;//D0--D2 �������
								 
								 
								 
			};
			unsigned char ctrl_code_area;
		};
		unsigned short int hcs;
	};
#pragma pack(pop)

	frame_header_struct *frame_header_;
	int is_send_packet_;

	unsigned short int get_crc(unsigned char* buffer,int length);
};
/*
class PTCL_CODEC_EXPORT ptcl_packet_hdlc : public ptcl_packet
{
public:
	ptcl_packet_hdlc(void);
	virtual ~ptcl_packet_hdlc(void);

	virtual void reset();

	//��װ���ģ�������set_packet_buffer
	virtual void format_packet();

	//�������� ������set_packet_buffer
	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_packet();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header();

	//����ֵ >0:�������ĳɹ� 0:���ĳ��Ȳ��� <0:���ĸ�ʽ����
	virtual int parse_header(unsigned char *buffer,int len_buffer);

	//�����ն��߼���ַ ���ձ���˳��
	virtual unsigned int get_device_addr();

	//���ر������к�
	virtual int get_frame_seq();

	//������վID
	virtual unsigned char get_host_id();

	void set_device_addr(unsigned int addr);

	unsigned char get_ctrl_code();
	void set_ctrl_code(unsigned char code);

	unsigned char get_header_start();

	unsigned short get_check_sum(unsigned char *buffer,int len,unsigned short fcs = 0xffff);

	void set_fcs_tab();

	void set_host_id(unsigned char host_id);

	unsigned char get_frame_header();

	unsigned char get_send_seq();
	void set_send_seq(unsigned char seq);

	unsigned char get_recv_seq();
	void set_recv_seq(unsigned char seq);

	void set_ctrl_flag(unsigned char flag);
	void set_ctrl_pf(unsigned char pf);

protected:
	//����ͷ�ṹ��
#pragma pack(push, 1)

	struct frame_header_struct
	{
		unsigned char frame_start;//0x7e
		union
		{
			struct
			{
				unsigned short	len			:	11,			//֡���� dlms���Ϊ0x0a
								s			:	1,			//s��־λ,˵��֡�Ƿ񱻷ָ�
								frame_type	:	4;			//֡����(��֡ͷ֡β��)
			};
			unsigned short int len_data_area;//֡������֡��
		};
		
		unsigned char device_addr[4];//Ŀ�ĵ�ַ��	��λ��ַĬ��Ϊ1 ����ʱ
		unsigned char host_id;	//Դ��ַ��
		union
		{
			struct  
			{
				unsigned char	flag		: 1,		//����֡����
								sss			: 3,		//P/F
								p_and_f		: 1,		//����֡����
								rrr			: 3;		//����
			};
			unsigned char ctrl_code_area; //������
		};
		
	};

#pragma pack(pop)

	frame_header_struct *frame_header_;
	unsigned short fcs_tab_[256];
};*/
