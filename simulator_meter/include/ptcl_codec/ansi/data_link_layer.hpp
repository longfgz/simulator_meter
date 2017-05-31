#ifndef LCLWH8V2L8S6M7N9_PUBLIC_PTCL_ANSI_C12_DOT18_DATA_LINK_LAYER
#define LCLWH8V2L8S6M7N9_PUBLIC_PTCL_ANSI_C12_DOT18_DATA_LINK_LAYER

#include "ptcl.hpp"
#include "macros.hpp"
#include "define_enum.hpp"
#include <deque>
#include <iterator>
#include <memory>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iterator>
#include <boost/make_shared.hpp>

enum
{
    NO_ERR = 0                    // �޴���
  , UNKNOWN_ERR                   // δ֪����
  , TIMEOUT_ERR                   // ��ʱ
  , PTCL_DECODE_ERR               // ��Լ��������
  , COMM_DEVICE_NOT_FOUND_ERR     // �Ҳ�����Ӧ��ͨѶ�豸
  , SERIAL_CLOSED_ERR             // �����Ѿ��ر�
  , DEV_NOTIFY_ABN_ERR            // �豸��Ӧ�쳣����Ϣ
};
typedef std::vector<byte_t> Message_AT;

template <typename ByteIt_T>
boost::shared_ptr<Message_AT> gen_msg_ptr(ByteIt_T begin, ByteIt_T end)
{
  boost::shared_ptr<Message_AT> ret_val = boost::make_shared<Message_AT>();
  std::copy(begin, end, std::insert_iterator<Message_AT>(*ret_val, ret_val->begin()));
  return ret_val;
}

// Todo_Sxc: 
// Ŀǰ��������ļ��迪�����Ժ���Ҫ������Ƴ���Щ����
// 1 ���͸���Ƶ�֡û�з���������
// 2 ��Ʒ�������֡Ҳû�з���������

namespace ptcl_utility { namespace ansi_c12 { namespace dot18 {
DEFINE_ENUM(DlState_ET, 
  ((BASE))
  ((ID))
  ((SESSION_NORMAL))
  ((SESSION_SECURITY))
);

// ��·����һ��һ��ķ�ʽ��һ����Է�Ϊ���飩

// ATTENTION !!!!!!!!!!!!
// ���ڵ��߳���ʹ�ô���
template <typename UpperLayer_T, typename LowerLayer_T>
class DataLinkLayer_CT 
  : public boost::enable_shared_from_this<DataLinkLayer_CT<UpperLayer_T, LowerLayer_T> >
{
private: TEST_ACCESS DataLinkLayer_CT(
             std::string const &password
           , LowerLayer_T &channel
           , std::unique_ptr<boost::asio::deadline_timer> timer
           , boost::asio::strand &strand);

public: void send(boost::shared_ptr<Message_AT> sdu, UpperLayer_T *sap);

public: void on_lower_sent(int error_code, boost::shared_ptr<Message_AT> frame);
public: void on_lower_receive(int error_code, boost::shared_ptr<Message_AT> buf);

private: TEST_ACCESS void send_next_frame();

private: TEST_ACCESS TEST_VIRTUAL void start_timeout_timer()
         { start_timer(boost::posix_time::seconds(TIME_OUT_SECOND)); }
private: TEST_ACCESS void start_timer(boost::posix_time::time_duration interval);

private: void handle_timer(boost::system::error_code const &e);

private: TEST_ACCESS template <typename ByteIt_T> 
         boost::shared_ptr<Message_AT> gen_frame(ByteIt_T first, ByteIt_T last);
private: inline boost::shared_ptr<Message_AT> gen_frame(boost::shared_ptr<Message_AT> sdu);
private: inline boost::shared_ptr<Message_AT> gen_ident_frame();
private: inline boost::shared_ptr<Message_AT> gen_logon_frame();
private: inline boost::shared_ptr<Message_AT> gen_security_frame();
private: inline boost::shared_ptr<Message_AT> gen_logoff_frame();
private: inline boost::shared_ptr<Message_AT> gen_terminate_frame();

private: void finish_sending_cur_frame(
             int error_code = NO_ERR
           , boost::shared_ptr<Message_AT> rcv_sdu = boost::shared_ptr<Message_AT>()
         );
private: void resend_cur_frame();

// ��ʱ�� begin
public: inline bool is_rcv_buf_empty() const { return i_rcv_buf.empty(); };
// ��ʱ�� end

private: TEST_ACCESS
  typedef DataLinkLayer_CT<UpperLayer_T, LowerLayer_T> ThisType_AT;
  typedef boost::array<byte_t, 20> Password_AT;

  static boost::shared_ptr<Message_AT> const c_ack;

  enum 
  { 
      TIME_OUT_SECOND = 3   // 3 ��û�� response �㳬ʱ
    , MAX_RESEND_TIMES = 3  // ����ط� 3 ��
    , MAX_IDLE_SECOND = 5   // �ŵ����Ŀ�������
  };   

  uint8_t i_toggle_bit;
  Password_AT i_password;

  // ��û�յ���Ӧ response�������ж�����ĵ�ǰ���ͱ���
  boost::shared_ptr<Message_AT> i_cur_req_frame;

  Message_AT i_rcv_buf;

  boost::asio::strand &i_strand;
  std::unique_ptr<boost::asio::deadline_timer> i_timer;
  uint8_t i_resend_count;     // �Ѿ��ط��Ĵ���

  LowerLayer_T &i_channel;    // �ײ�ͨѶͨ����������Ӧ�ó��ڴ���Ķ���

  DlState_ET i_state;
  
  // ATTENTION !!!!!!!!!!!!
  // UpperLayer_T ָ������ڷ��ط��ͱ��ĵ� response ����֮ǰһֱ��Ч��
  // ������ܱ�֤������ʹ�� weak_ptr ���������������м���ɾ�� DataLinkLayer_CT �б�������ָ�룬
  // ���磬���� cancle_send(UpperLayer_T *sap) ��Ա������
  std::deque<
    std::pair<boost::shared_ptr<Message_AT>, UpperLayer_T*> 
  > i_sdus;  // ��Ҫ���͵��ϲ㱨��

template <typename U, typename L>
friend boost::shared_ptr<DataLinkLayer_CT<U, L> > make_data_link(
    std::string const &password
  , L &channel
  , std::unique_ptr<boost::asio::deadline_timer> timer
  , boost::asio::strand &strand
);
};

template <typename U, typename L> 
inline boost::shared_ptr<DataLinkLayer_CT<U, L> >
make_data_link(
    std::string const &password
  , L &channel
  , std::unique_ptr<boost::asio::deadline_timer> timer
  , boost::asio::strand &strand)
{
  return boost::shared_ptr<DataLinkLayer_CT<U, L> >(
    new DataLinkLayer_CT<U, L>(password, channel, std::move(timer), strand));
}
}}} // namespace ptcl_utility::ansi_c12::dot18



/** ------------------------------- INLINE ------------------------------- **/
namespace ptcl_utility { namespace ansi_c12 { namespace dot18 {
template <typename U, typename L>
boost::shared_ptr<Message_AT> const DataLinkLayer_CT<U,L>::c_ack(new Message_AT(1, ACK));

template <typename U, typename L> 
DataLinkLayer_CT<U, L>::DataLinkLayer_CT(
    std::string const &password
  , L &channel
  , std::unique_ptr<boost::asio::deadline_timer> timer
  , boost::asio::strand &strand
)
  : i_toggle_bit(0)
  , i_timer(std::move(timer))
  , i_resend_count(0)
  , i_channel(channel)
  , i_state(DlState_ET::BASE)
  , i_strand(strand)
{
  char pad = ' ';
  size_t copy_len = std::min<size_t>(password.size(), sizeof(Password_AT));
  auto it = password.begin();
  std::copy(it, it + copy_len, i_password.begin());
  if (copy_len < sizeof(Password_AT))
  {
    std::for_each(i_password.begin() + copy_len, i_password.end(),
      [pad](byte_t &v){ v = pad; });
  }
}

template <typename U, typename L> 
void 
DataLinkLayer_CT<U, L>::send(
    boost::shared_ptr<Message_AT> sdu
  , U *sap
)
{
  bool send_in_progress = !i_sdus.empty();
  i_sdus.push_back(std::make_pair(sdu, sap));
  if (!send_in_progress) { send_next_frame(); }
}

template <typename U, typename L> 
void DataLinkLayer_CT<U, L>::send_next_frame()
{
  if (i_cur_req_frame) { return; }
  if (!i_sdus.empty())
  {
    switch (i_state)
    {
    case DlState_ET::BASE:
      i_cur_req_frame = gen_ident_frame();
      break;
    case DlState_ET::ID:
      i_cur_req_frame = gen_logon_frame();
      break;
    case DlState_ET::SESSION_NORMAL:
      i_cur_req_frame = gen_security_frame();
      break;
    case DlState_ET::SESSION_SECURITY:
      i_cur_req_frame = gen_frame(i_sdus.front().first);
      break;
    default:
      return;
      break;
    }
  }
  else
  {
    switch (i_state)
    {
    case DlState_ET::BASE:
      return;
      break;
    case DlState_ET::ID:
      i_cur_req_frame = gen_terminate_frame();
      break;
    case DlState_ET::SESSION_NORMAL:
    case DlState_ET::SESSION_SECURITY:
      i_cur_req_frame = gen_logoff_frame();
      break;
    default:
      break;
    }
  }
  i_channel.send(i_cur_req_frame);
  start_timeout_timer();
}

template <typename U, typename L> 
template <typename ByteIt_T> 
boost::shared_ptr<Message_AT> 
DataLinkLayer_CT<U, L>::gen_frame(
    ByteIt_T first
  , ByteIt_T last
)
{
  boost::shared_ptr<Message_AT> ret_val(new Message_AT());
  uint16_t data_len = static_cast<uint16_t>(std::distance(first, last));
  ret_val->resize(sizeof(FrameHead_CT) + data_len + 2);
  FrameHead_CT *head = reinterpret_cast<FrameHead_CT *>(&*(ret_val->begin()));
  head->init(data_len, i_toggle_bit);
  std::copy(first, last, ret_val->begin() + sizeof(FrameHead_CT));
  Crc_AT crc_func;
  auto crc_it = ret_val->end() - 2;
  crc_func = std::for_each(ret_val->begin(), crc_it, crc_func);
  uint16_t *crc = reinterpret_cast<uint16_t*>(&*crc_it);
  *crc = crc_func();
  return ret_val;
}

template <typename U, typename L> 
boost::shared_ptr<Message_AT> 
DataLinkLayer_CT<U, L>::gen_frame(boost::shared_ptr<Message_AT> sdu)
{
  return gen_frame(sdu->begin(), sdu->end());
}

template <typename U, typename L> 
boost::shared_ptr<Message_AT> DataLinkLayer_CT<U, L>::gen_ident_frame()
{
  static byte_t sdu[] = { REQ_IDENT };
  return gen_frame(std::begin(sdu), std::end(sdu));
}

template <typename U, typename L> 
boost::shared_ptr<Message_AT> DataLinkLayer_CT<U, L>::gen_logon_frame()
{
  static byte_t sdu[] = { 
    REQ_LOGON, 
    0x00, 0x01,   /* user-id: д��Ϊ���֡�1�� */
    0x20, 0x20, 0x20, 0x20, 0x20, 
    0x20, 0x20, 0x20, 0x20, 0x31  /* user: д��Ϊ����Ϊʮ���ַ������Ÿ��ո��һ�� 1 */
  };
  return gen_frame(std::begin(sdu), std::end(sdu));
}

template <typename U, typename L> 
boost::shared_ptr<Message_AT> DataLinkLayer_CT<U, L>::gen_security_frame()
{
  boost::array<byte_t, 1 + sizeof(Password_AT)> sdu;
  sdu.front() = REQ_SECURITY;
  std::copy(i_password.begin(), i_password.end(), sdu.begin() + 1);
  return gen_frame(std::begin(sdu), std::end(sdu));
}

template <typename U, typename L> 
boost::shared_ptr<Message_AT> DataLinkLayer_CT<U, L>::gen_logoff_frame()
{
  static byte_t sdu[] = { REQ_LOGOFF };
  return gen_frame(std::begin(sdu), std::end(sdu));
}

template <typename U, typename L> 
boost::shared_ptr<Message_AT> DataLinkLayer_CT<U, L>::gen_terminate_frame()
{
  static byte_t sdu[] = { REQ_TERMINATE };
  return gen_frame(std::begin(sdu), std::end(sdu));
}

template <typename U, typename L>
void 
DataLinkLayer_CT<U, L>::finish_sending_cur_frame(
    int error_code
  , boost::shared_ptr<Message_AT> rcv_sdu
)
{
  i_cur_req_frame.reset();
  i_resend_count = 0;
  bool sending_sdu_finished = 
    !i_sdus.empty() && ( NO_ERR != error_code || rcv_sdu );
  if (sending_sdu_finished)
  {
    U *upper_layer = i_sdus.front().second;
    if (nullptr != upper_layer)
      { upper_layer->receive(error_code, rcv_sdu); }
    i_sdus.pop_front();

    // �ոձ䱻�գ����ֵ�ǰ״̬һС��ʱ��
    if (i_sdus.empty()) 
    { 
      start_timer(boost::posix_time::seconds(MAX_IDLE_SECOND));
      return;
    } 
  }
  send_next_frame();
}

template <typename U, typename L>
void DataLinkLayer_CT<U, L>::resend_cur_frame()
{
  assert(i_cur_req_frame);
  if (!i_cur_req_frame) { return; }
  i_channel.send(i_cur_req_frame);
  start_timeout_timer();
  ++i_resend_count;
}

template <typename U, typename L>
void DataLinkLayer_CT<U, L>::start_timer(
  boost::posix_time::time_duration interval
)
{
  if (!i_timer) { return; }
  i_timer->expires_from_now(interval);
  i_timer->async_wait(boost::bind(&ThisType_AT::handle_timer, 
    shared_from_this(), boost::asio::placeholders::error));
}

template <typename U, typename L>
void DataLinkLayer_CT<U, L>::handle_timer(boost::system::error_code const &e)
{
  if (e == boost::asio::error::operation_aborted) { return; }
  if (i_cur_req_frame) 
  {
    if (i_resend_count < MAX_RESEND_TIMES)
    {
      resend_cur_frame();
    }
    else 
    {
      i_state = DlState_ET::BASE;
      finish_sending_cur_frame(TIMEOUT_ERR); 
    }
  }
  else { send_next_frame(); }
}

template <typename U, typename L>
void DataLinkLayer_CT<U, L>::on_lower_sent(
    int error_code
  , boost::shared_ptr<Message_AT> frame
)
{
  assert(frame == i_cur_req_frame);
  if (NO_ERR != error_code) 
  {
    i_state = DlState_ET::BASE;
    finish_sending_cur_frame(error_code); 
  }
}

template <typename U, typename L>
void 
DataLinkLayer_CT<U, L>::on_lower_receive(
    int error_code
  , boost::shared_ptr<Message_AT> buf
)
{
  if (NO_ERR != error_code) 
  { 
    i_state = DlState_ET::BASE;
    finish_sending_cur_frame(error_code);
    return;
  }

  // Todo_Sxc: ��������Ż������� i_rcv_buf Ϊ�յ�ʱ��ֱ�ӽ��� buf��
  //           ��������������ġ�
  auto old_size = i_rcv_buf.size();
  i_rcv_buf.resize(old_size + buf->size());
  std::copy(buf->cbegin(), buf->cend(), i_rcv_buf.begin() + old_size);
  
  std::pair<Message_AT::const_iterator, Message_AT::const_iterator> range;
  uint16_t data_len;
  FrameType_ET type = FrameType_ET::FT_NONE;
  auto unread_it = i_rcv_buf.cbegin();

  do
  {
    type = get_frame(unread_it, i_rcv_buf.cend(), range, data_len);
    if (FrameType_ET::FT_ACK == type)
    {
      unread_it = range.second;
      if (NAK == *range.first) { resend_cur_frame(); }
      else { start_timeout_timer(); }
    }
    else if (FrameType_ET::FT_DATA == type)
    {// Todo_Sxc: 
      unread_it = range.second;
      
      i_channel.send(c_ack);
      
      FrameHead_CT const *head = reinterpret_cast<FrameHead_CT const*>(&*range.first);
      if (i_toggle_bit != head->get_toggle_bit()) { continue; }
      i_toggle_bit = (0 == i_toggle_bit) ? 1 : 0;

      // ע�⣺�����Ӧ��֡�����ǵ�һ֡��û�� response code
      uint8_t response_code = *( range.first + sizeof(FrameHead_CT) );
      if (RSP_ISSS == response_code)
      {
        i_state = DlState_ET::BASE;
        finish_sending_cur_frame();
      }
      else if (RSP_OK == response_code)
      {
        switch (i_state)
        {
        case DlState_ET::BASE:  
          i_state = i_sdus.empty() ? DlState_ET::BASE : DlState_ET::ID;
          finish_sending_cur_frame();
          break;
        case DlState_ET::ID:
          i_state = i_sdus.empty() ? DlState_ET::BASE : DlState_ET::SESSION_NORMAL;
          finish_sending_cur_frame();
          break;
        case DlState_ET::SESSION_NORMAL:
          i_state = i_sdus.empty() ? DlState_ET::ID : DlState_ET::SESSION_SECURITY;
          finish_sending_cur_frame();
          break;
        case DlState_ET::SESSION_SECURITY:
          {
            if (i_sdus.empty()) 
            { 
              i_state = DlState_ET::ID;
              finish_sending_cur_frame();
            }
            else
            {
              boost::shared_ptr<Message_AT> rcv_sdu(new Message_AT(data_len));
              auto data_it = range.first + sizeof(FrameHead_CT);
              std::copy(data_it, data_it + data_len, rcv_sdu->begin());
              finish_sending_cur_frame(NO_ERR, rcv_sdu);
            }
          }
          break;
        default:
          break;
        }
      }
      else
      {
        if (i_sdus.empty()) 
        { 
          i_state = DlState_ET::BASE;
          finish_sending_cur_frame();
        }
        else
        { finish_sending_cur_frame(DEV_NOTIFY_ABN_ERR); }
      }
    }
  } while (FrameType_ET::FT_NONE != type);
  i_rcv_buf.erase(i_rcv_buf.cbegin(), unread_it);
}
}}} // namespace ptcl_utility::ansi_c12::dot18

#endif  // #ifndef LCLWH8V2L8S6M7N9_PUBLIC_PTCL_ANSI_C12_DOT18_DATA_LINK_LAYER
