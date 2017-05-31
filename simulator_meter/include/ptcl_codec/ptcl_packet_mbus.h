#include <ptcl_codec/ptcl_packet.h>


class PTCL_CODEC_EXPORT ptcl_packet_mbus : public ptcl_packet
{
	public:
	ptcl_packet_mbus(int packet_type = 1);
	virtual ~ptcl_packet_mbus(void);

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

	unsigned int get_serial_number();

	unsigned short int get_macfacture();

	unsigned char get_version();

	unsigned char get_device_type();

	unsigned char get_ci();

	unsigned char get_access_no();

	unsigned char get_status();

	unsigned short int get_signature();

	unsigned int get_ci_s_id();

	unsigned char get_ci_version();

	unsigned char get_ci_device_type();

	void set_status(unsigned char status);


protected:
	//����ͷ�ṹ��
#pragma pack(push, 1)
	struct frame_header_struct_7a
	{
		unsigned char len;

		unsigned char c;		//0x44

		unsigned short int man_id;  //manufacture id

		unsigned int s_number;

		unsigned char version;
		unsigned char device_type;

		unsigned char ci;

		unsigned char access_no;
		unsigned char status;
		unsigned short int signature;
	};

	struct frame_header_struct_72
	{
		unsigned char len;

		unsigned char c;		//0x44

		unsigned short int man_id;  //manufacture id

		unsigned int s_number;

		unsigned char version;
		unsigned char device_type;

		unsigned char ci;

		unsigned int ci_s_id;
		unsigned short int ci_man_id;
		unsigned char ci_version;
		unsigned char ci_device_type;
		unsigned char access_no;
		unsigned char status;
		unsigned short int signature;
	};

#pragma pack(pop)

	struct frame_header_struct_7a *frame_header_7a_;

	struct frame_header_struct_72 *frame_header_72_;

	int packet_type_;

};