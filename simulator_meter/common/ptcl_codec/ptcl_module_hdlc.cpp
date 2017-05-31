#include <ptcl_codec/ptcl_module_hdlc.h>
#include <ptcl_codec/asn_codec.h>
#include <time.h>
#include <stdio.h>

ptcl_module_hdlc *ptcl_module_hdlc::instance_ = NULL;
ptcl_module_hdlc::ptcl_module_hdlc(void)
{

}

ptcl_module_hdlc::~ptcl_module_hdlc(void)
{

}

ptcl_module_hdlc *ptcl_module_hdlc::get_instance()
{
	if (instance_ == NULL)
	{
		instance_ = new ptcl_module_hdlc;
	}
	return instance_;
}

void ptcl_module_hdlc::format_packet_hdlc_connect(ptcl_packet_hdlc *packet,
								short int max_send_bytes,short int max_recv_bytes,
								int send_window,int recv_window)
{
	//��վID
	packet->set_host_id(host_id_);

	//����������
	packet->set_ctrl_code_area(ctrl_code_snrm);//SNRM

	unsigned char buf_data_area[] = {
		0x81,//��ʽ��ʶ��
		0x80,//���ʶ��
		0x14,//��������
		0x05,0x02,0x04,0x00,//���������Ϣ����1024
		0x06,0x02,0x04,0x00,//���������Ϣ����1024
		0x07,0x04,0x00,0x00,0x00,0x01, //���ʹ��ڴ�С1
		0x08,0x04,0x00,0x00,0x00,0x07}; //���մ��ڴ�С1

	packet->set_data_area_buffer(buf_data_area, 23);
	packet->format_packet();

}

void ptcl_module_hdlc::format_packet_hdlc_disconnect(ptcl_packet_hdlc *packet)
{
	//��վID
	packet->set_host_id(host_id_);

	//����������
	packet->set_ctrl_code_area(ctrl_code_disc);//DISC

	packet->format_packet();
}

void ptcl_module_hdlc::dlms2hdlc(ptcl_packet_hdlc *packet, ptcl_packet_dlms47 *packet47, int recv_seq, int send_seq)
{
		//��վID
	packet->set_host_id(host_id_);

	//����������
	packet->set_cca_recv_seq(recv_seq);
	packet->set_cca_pf(1);
	packet->set_cca_send_seq(send_seq);
	packet->set_cca_end(0);

	//�û�������
	unsigned char buf_data_area[1024];
	int length = 0;
	//LLC
	buf_data_area[length++] = 0xE6;
	buf_data_area[length++] = 0xE6;
	buf_data_area[length++] = 0x00;
	memcpy(buf_data_area+length, packet47->get_data_area_buffer(), packet47->get_data_area_length());
	length += packet47->get_data_area_length();
	packet->set_data_area_buffer(buf_data_area, length);

	packet->format_packet();
}


void ptcl_module_hdlc::hdlc2dlms(ptcl_packet_hdlc *packet, ptcl_packet_dlms47 *packet47)
{
	packet47->set_host_id(1);
	packet47->set_device_addr(1);
	packet47->set_data_area_buffer(packet->get_data_area_buffer()+3, packet->get_data_area_length()-3);
	packet47->format_packet();
}


