//------------------------------------------------------------
// @file		log.cpp
// @brief	���O
// @detail	���O�̏o�͂��T�|�[�g���܂�
//------------------------------------------------------------
#include "log.h"
#include <regex>
#include <fstream>
using namespace std;

// �ÓI�����o�ϐ��̏�����
std::vector<Log::LogData> Log::m_logDatas;

//=============================================================
// ���O�̑��M
//=============================================================
void Log::SendLog(std::string message, TYPE type)
{
	// ���O�f�[�^���쐬����
	LogData data;
	data.type = type;
	data.message = message;

    // ����
    data.time = time(nullptr);
        
#if SHOW_LOG_TERMINAL
	// ���O���^�[�~�i���ɏo�͂���
	OutputDebugString(WriteLog(data).c_str());
#endif

    // �f�[�^��ۑ�����
    m_logDatas.push_back(data);
}

//=============================================================
// ���O�f�[�^���烍�O���𐶐�����
//=============================================================
std::string Log::WriteLog(LogData data)
{
    // ���O�̃e���v���[�g��ݒ肷��
    string log_template = LOG_TEMPLATE;

    // ���Ԃ�u��������
    regex patternTime("%time");

    // ���Ԃ��e�L�X�g�ɋN����
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&data.time));
    log_template = regex_replace(log_template, patternTime, buffer);

    // ���O�̎�ނ�u��������
    regex patternType("%type");
    string type_char = "";
    switch (data.type)
    {
    case TYPE_NORMAL:
        type_char = LOG_TAG_NORMAL;
        break;
    case TYPE_WARNING:
        type_char = LOG_TAG_WARNING;
        break;
    case TYPE_ERROR:
        type_char = LOG_TAG_ERROR;
        break;
    }
    log_template = regex_replace(log_template, patternType, type_char);

    // ���b�Z�[�W��u��������
    regex patternMessage("%message");
    log_template = regex_replace(log_template, patternMessage, data.message);

    // �Ԃ�
    return log_template;
}

//=============================================================
// ���O���t�@�C���Ƃ��ďo�͂���
//=============================================================
void Log::OutputLog()
{
    // ���O�̃p�X��ݒ肷��
    string log_output = OUTPUT_LOG_PATH;

    // ���Ԃ��e�L�X�g�ɋN����
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%d-%m %H.%M.%S", now);

    // ������u��������
    regex patternData("%data");
    log_output = regex_replace(log_output, patternData, buffer);

    // �t�@�C���ɏ����o��
    ofstream output;
    output.open(log_output, ios::out);
    for (auto itr = m_logDatas.begin(); itr != m_logDatas.end(); itr++)
    {
        output << WriteLog(*itr);
    }
    output.close();
}