/*�g�p�����{�I�Ȋ֐��Z�b�g*/

#pragma once


class BasicFunc {
public:
	virtual void Initialize() = 0;	// ����������
	virtual void Finalize() = 0;	// �I������
	virtual void Update() = 0;	// �X�V����
	virtual void Draw() = 0;	// �`�揈��
};
