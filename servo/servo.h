/***************************************************************************
 *	@�t�@�C����		:	servo.h
 *	@�T�v		:	DIGITAL-IO�|�[�g�Ń��[�^�𐧌䂷�邽�߂�PFM�������Ɠ�����s���D
 *	@�o�[�W����		:	1.2.0
 *	@�J����			:	saka
 *	@�g�p��		:	STM32F4DISCOVERY, MB_Ver2, Coocox CoIDE
 **************************************************************************/
typedef struct
{
	short high[8];
	short low[8];
	short cnt[8];
} _servo_status_t;

/* �֐��v���g�^�C�v�錾	===================================================== */
/* -------------------------------------------------
 * @�֐���		:	Motor_Drive
 * @�T�v			:	���[�^�|�[�g����PFM���o�͂���A
 * 				:	high,low[ns]���w��(0,0)�ɏo��
 * @�߂�l		:	�Ȃ�
 * ---------------------------------------------- */
void Servo_Drive(short high,short low);

//����Ȋ֐��K�v�Ȃ��ł���
//void ServoDriver_Init(u16 motors);