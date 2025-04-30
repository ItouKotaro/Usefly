//------------------------------------------------------------
// @file		gizmo.h
// @brief	�M�Y��
// @detail �M�Y���@�\��񋟂��܂�
//------------------------------------------------------------
#ifndef _GIZMO_H_
#define _GIZMO_H_

// �M�Y��
#define Gizmo GizmoSystem::GetInstance()

/**
 * @brief �M�Y���V�X�e��
*/
class GizmoSystem final
{
public:
	//@brief �C���X�^���X���擾����
	static GizmoSystem& GetInstance()
	{
		static GizmoSystem instance;
		return instance;
	}

	//@brief 3D�����_�����O����
	void Render3D();
	//@brief 2D�����_�����O����
	void Render2D();

	//@brief ���C����`�悷��
	void DrawLine(const D3DXVECTOR3& from, const D3DXVECTOR3& to, const D3DXCOLOR& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	//@brief 2D���C����`�悷��
	void DrawLine2D(const D3DXVECTOR2& from, const D3DXVECTOR2& to, const float& bold = 1.0f, const D3DXCOLOR& color = { 1.0f, 1.0f, 1.0f, 1.0f });
	//@brief �����`��2D���C����`�悷��
	void DrawRectangle(const D3DXVECTOR2& start, const D3DXVECTOR2& size, const float& bold = 1.0f, const D3DXCOLOR& color = { 1.0f, 1.0f, 1.0f, 1.0f }, const float& angle = 0.0f);

private:
	//@brief �M�Y���I�u�W�F�N�g
	template<class T> class GizmoObject
	{
	public:
		GizmoObject() : m_life(30), m_use(true) {};

		/**
		 * @brief �X�V
		 * @return �j���^�C�~���O
		*/
		bool Update()
		{
			if (!m_use)
			{
				m_life--;
				return true;
			}
				
			m_life = 30;
			return false;
		}

		//@brief �g�p��Ԃ��擾����
		bool& GetUse() { return m_use; }

		//@brief �擾
		T& Get() { return m_obj; }
	private:
		T m_obj;
		int m_life;
		bool m_use;
	};
	
	//@brief ���C��3D
	class Line3D
	{
	public:
		void Init();
		void Uninit();
		void Draw();
		void Set(const D3DXVECTOR3& from, const D3DXVECTOR3& to, const D3DXCOLOR& color);
	private:
		LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
	};
	//@brief ���C��2D
	class Line2D
	{
	public:
		void Init();
		void Uninit();
		void Draw();
		void Set(const D3DXVECTOR2& from, const D3DXVECTOR2& to, const float& bold, const D3DXCOLOR& color);
	private:
		LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
	};

private:
	// �M�Y���I�u�W�F�N�g�̊Ǘ�
	std::vector<GizmoObject<Line3D>> m_line3d;
	std::vector<GizmoObject<Line2D>> m_line2d;
};


#endif // !_GIZMO_H_
