//------------------------------------------------------------
// @file		log.h
// @brief	���O
// @detail	���O�̏o�͂��T�|�[�g���܂�
//------------------------------------------------------------
#ifndef _LOG_H_
#define _LOG_H_

//-----------------------------------------------------------
// �ݒ荀��

// ���O���^�[�~�i���ɏo�͂��邩
#define SHOW_LOG_TERMINAL	(true)

// ���O���t�@�C���Ƃ��ďo�͂��邩
#define OUTPUT_LOG_FILE		(true)

// ���O��ۑ�����p�X
#define OUTPUT_LOG_PATH		"logs\\log-%data.txt"

// ���O�e���v���[�g
#define LOG_TEMPLATE				"%time > [%type] %message\n"

// �^�O�̐ݒ�
#define LOG_TAG_NORMAL		"LOG"
#define LOG_TAG_WARNING		"WARNING"
#define LOG_TAG_ERROR			"ERROR"

//-----------------------------------------------------------


//@brief ���O�N���X
class Log final
{
public:
	//@brief ���
	enum TYPE
	{
		TYPE_NORMAL,		// �ʏ�
		TYPE_WARNING,	// ����
		TYPE_ERROR,		// �G���[
	};

	//@brief ���O�f�[�^
	struct LogData
	{
		TYPE type;					// ���
		std::string message;	// ���b�Z�[�W
		time_t time;					// ����
	};

	//@brief ���O�𑗐M����
	//@param message: ���M���郁�b�Z�[�W
	//@param type: ���O�̎��
	static void sendLog(std::string message, TYPE type = TYPE_NORMAL);

	//@brief ���O�f�[�^���烍�O���𐶐�����
	static std::string writeLog(LogData data);

	//@brief ���O���t�@�C���Ƃ��ďo�͂���
	static void outputLog();

private:
	static std::vector<LogData> m_logDatas;	// ���O�̃f�[�^
};

#endif // !_LOG_H_
