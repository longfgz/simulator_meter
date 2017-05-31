#pragma once

#include <ptcl_codec/ptcl_packet.h>

class PTCL_CODEC_EXPORT ptcl_packet_sg : public ptcl_packet
{
public:
	ptcl_packet_sg(void);
	virtual ~ptcl_packet_sg(void);

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
	void set_device_addr(unsigned int addr);

	//��վ��ַ��
	unsigned char get_host_id_area();
	void set_host_id_area(unsigned char area);

	//��վ��ַ
	void set_host_id(unsigned char id);

	//֡���
	void set_frame_seq(unsigned char seq);

	//����������
	unsigned char get_afn_ctrl();
	void set_afn_ctrl(unsigned char afn);

	//֡������Чλ
	unsigned char get_fcv();
	void set_fcv(unsigned char fcv);

	//֡����λ
	unsigned char get_fcv_acd();
	void set_fcv_acd(unsigned char fcv_acd);

	//������־λ
	unsigned char get_frm();
	void set_frm(unsigned char frm);

	//���䷽��
	unsigned char get_dir();
	void set_dir(unsigned char dir);

	//��������
	unsigned char get_ctrl_code_area();
	void set_ctrl_code_area(unsigned char area);

	//�ն����ַ
	unsigned char get_group_addr();
	void set_group_addr(unsigned char group_addr);

	//Ӧ�ò㹦����
	unsigned char get_afn();
	void set_afn(unsigned char afn);
	
	//����ȷ�ϱ�־λ
	unsigned char get_con();
	void set_con(unsigned char con);

	//����֡��־
	unsigned char get_fin();
	void set_fin(unsigned char fin);

	//��֡��־
	unsigned char get_fri();
	void set_fri(unsigned char fri);

	//֡ʱ���ǩ��Чλ
	unsigned char get_tpv();
	void set_tpv(unsigned char tpv);

	//�������ֶ�
	unsigned char get_seq_area();
	void set_seq_area(unsigned char area);


	void set_ptcl_flag(unsigned char flag);

	unsigned char get_ptcl_flag();
	////���ݵ�Ԫ
	//struct pnfn_data
	//{
	//	int pn;
	//	int fn;
	//};


	//static int format_pnfn(pnfn_data *pnfn,unsigned char *buffer,bool is_sg04 = false);
	//static int parse_pnfn(unsigned char *buffer,pnfn_data *pnfn,bool is_sg04 = false);

	////�¼�������
	//struct ec_data
	//{
	//	unsigned char important_ec;//��Ҫ�¼�������
	//	unsigned char generic_ec;//��ͨ�¼�������
	//};
	////�¼�������
	//static int format_ec(ec_data *ec,unsigned char *buffer);
	//static int parse_ec(unsigned char *buffer,ec_data *ec);

	////ʱ���ʶ
	//struct tp_data
	//{
	//	unsigned char pfc;//����֡֡��ż�����
	//	unsigned char sec;//��
	//	unsigned char min;//��
	//	unsigned char hour;//ʱ
	//	unsigned char day;//��
	//	unsigned char time_out;//��ʱʱ��
	//};
	////ʱ���ǩ
	//static int format_tp(tp_data *tp,unsigned char *buffer);
	//static int parse_tp(unsigned char *buffer,tp_data *tp);

	//int get_aux_len();

protected:
	//����ͷ�ṹ��
#pragma pack(push, 1)
	struct frame_header_struct
	{
		unsigned char frame_start;//0x68
		union 
		{
			struct
			{
				unsigned short int    ptcl_flag		:	 2 ,//D0--D1��Լ��ʾ
									  len_data_area	:	 14 ;//D2--D15���ȣ������򡢵�ַ����·�û����ݳ���������
			};
			unsigned short int len_area;  
		};
		unsigned short int len_area_ex;
		unsigned char data_area_start;//0x68
		union 
		{
			struct
			{
				unsigned char	afn_ctrl : 4 ,//D0--D3����������
								fcv		 : 1 ,//D4֡������Чλ
								fcb_acd	 : 1 ,//D5֡����λ ���� �������λ
								frm		 : 1 ,//D6������־λ
								dir		 : 1 ;//D7���䷽��λ
			};
			unsigned char ctrl_code_area;
		};
		unsigned char device_addr[4];//�ն��߼���ַ
		union 
		{
			struct
			{
				unsigned char   group_addr	:	 1 ,//D0 �ն����ַ
								host_id		:	 7 ;//D1-D7��վ��ַ
			};
			unsigned char host_id_area;
		};
		unsigned char afn;
		union 
		{
			struct
			{
				unsigned char    frame_seq	:	 4 ,//D0--D3֡���
								 con		:	 1 ,//D4����ȷ�ϱ�־λ
								 fin		:	 1 ,//D5����֡��־
								 fri		:	 1 ,//D6��֡��־
								 tpv		:	 1 ;//D7֡ʱ���ǩ��Чλ
			};
			unsigned char seq_area;
		};
	};

	////���ݵ�Ԫ�ṹ
	//struct pnfn_struct
	//{
	//	unsigned char pn[2];
	//	unsigned char fn[2];
	//};

#pragma pack(pop)

	frame_header_struct *frame_header_;
};
