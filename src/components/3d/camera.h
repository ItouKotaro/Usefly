//------------------------------------------------------------
// @file		camera.h
// @brief	�J����
// @detail	3D��Ԃɑ��݂���I�u�W�F�N�g��`�悷�邽�߂̃f�o�C�X
//------------------------------------------------------------
#ifndef _COMP_CAMERA_H_
#define _COMP_CAMERA_H_

#include "component.h"

// ��`
constexpr float CLIPPING_NEAR = 0.1f;			// �ŒZ�`�拗��
constexpr float CLIPPING_FAR = 2000.0f;			// �ō��`�拗��
constexpr float CAMERA_LENGTH = 100.0f;		// ���_�ƒ����_�̋���

//@brief �J�����R���|�[�l���g
class Camera : public Component
{
public:
	//@brief ���e���[�h
	enum MODE
	{
		MODE_PERSPECTIVE,		// �������e
		MODE_PARALLEL,			// ���s���e
	};

	//@brief ������
	void Init() override;
	//@brief �I��
	void Uninit() override;
	//@brief �X�V
	void Update() override;

	//@brief ������x�N�g����ݒ肷��
	void SetVectorUp(D3DXVECTOR3 up) { m_vecU = up; }
	//@brief ���_�ƒ����_�̋�����ݒ肷��
	void SetLength(float length) { m_length = length; }
	//@brief �ŒZ�`�拗����ݒ肷��
	void SetClippingPlaneNear(float value) { m_clippingPlanes.min = value; }
	//@brief �ō��`�拗����ݒ肷��
	void SetClippingPlaneFar(float value) { m_clippingPlanes.max = value; }
	//@brief ���e���[�h��ݒ肷��
	void SetMode(MODE mode) { m_mode = mode; }

	//@brief ������x�N�g�����擾����
	D3DXVECTOR3 GetVectorUp() { return m_vecU; }
	//@brief ���_�ƒ����_�̋������擾����
	float GetLength() { return m_length; }
	//@brief �ŒZ�`�拗�����擾����
	float GetClippingPlaneNear() { return m_clippingPlanes.min; }
	//@brief �ō��`�拗�����擾����
	float GetClippingPlaneFar() { return m_clippingPlanes.max; }
	//@brief ���e���[�h���擾����
	MODE GetMode() { return m_mode; }

	//@brief �r���[�|�[�g�̈ʒu��ݒ肷��
	void SetViewportPosition(float x, float y);
	//@brief �r���[�|�[�g�̃T�C�Y��ݒ肷��
	void SetViewportSize(float width, float height);

	//@brief �J�����̐ݒu
	void SetCamera();

	//@brief ���ׂẴJ�������擾����
	static const std::vector<Camera*>& GetAllCameras() { return m_cameras; }
private:
	D3DXVECTOR3 m_posR;				// �����_
	D3DXVECTOR3 m_vecU;				// ������x�N�g��
	float m_length;							// ���_�ƒ����_�̋���
	Range<float> m_clippingPlanes;	// �`��͈�
	MODE m_mode;							// ���e���[�h

	D3DXMATRIX m_projMtx;			// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_viewMtx;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;		// �r���[�|�[�g

	static std::vector<Camera*> m_cameras;
};

#endif // !_COMP_CAMERA_H_
