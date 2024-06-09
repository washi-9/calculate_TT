#include <stdio.h>
/* ���� ���� */

/* ������\���\���� */
typedef struct time {
    int hours;
    int minutes;
}Time;

/* �H���f�[�^��\���\���� */
typedef struct process {
    char *event; // �H���̖��O
    char *information; // �H���̐���
    int nkm; // �H���̋���(km)
    int nup; // �H���̃A�b�v
    int ndown; // �H���̃_�E��
    int duration; // �H���̏��v����(��)
}Process;

/* �����̉��Z�֐� */
Time addTime(Time start, int minutes) {
    Time result;
    result.hours = start.hours + (start.minutes + minutes) / 60; // ���Ԃ̉��Z
    result.minutes = (start.minutes + minutes) % 60; // ���̉��Z
    return result;
}

/* �X�P�W���[���̌v�Z�֐� */
void calculateSchedule(Time startTime, Process processes[], int numProcesses ) {
    Time currentTime = startTime;
    int totalDistance = 0, totalUp = 0, totalDown = 0;

    /* �e�H���̋����A�b�v�_�E�������v���� */
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].nkm > 0) totalDistance += processes[i].nkm;
        if (processes[i].nup > 0) totalUp += processes[i].nup;
        if (processes[i].ndown > 0) totalDown += processes[i].ndown;
    }

    printf("%dkm %ddown %ddown\n\n", totalDistance, totalUp, totalDown);

    for (int i = 0; i < numProcesses; i++) {
        printf("%02d:%02d %s\n",currentTime.hours, currentTime.minutes, processes[i].event);
        if (i == numProcesses - 1) break; // �Ō�̍H���̏ꍇ����\�����Ȃ�
        /* �Œ�̎��Ԃ̕\���̔���(min��h��) */
        int judge = processes[i].duration % 60;
        /* �ړ����Ԃ�0�̏ꍇ */
        if (processes[i].duration == 0) {
            judge = 1;
        }
        /* hour��h�ɕϊ����ꂽ���Ԃ��i�[ */
        int hour = processes[i].duration / 60;
        printf("  ��%s ", processes[i].information);
        /* km�ŏ������� */
        switch (processes[i].nkm) {
            case 0: /* 0km�̏ꍇ */
                /* up down��0�ł��邽�ߎ��Ԃ����\�� */
                switch (judge) {
                    case 0: /* h�\�� */
                        printf("%dh\n", hour);
                        break;
                    case 30: /*n.5h */
                        printf("%d.5h\n", hour);
                        break;
                    case 1: /* �ړ����Ԃ�0 */
                        printf("\n");
                        break;
                    default: /* min�\�� */
                        printf("%dmin\n", processes[i].duration);
                        break;
                }
                break;
// �����܂ł�0km�̏ꍇ
            case (-1): /* ��km */
                printf("��km ");
                switch (processes[i].nup) {
                    case 0: /* up��0�̏ꍇ */
                        break;

                    case (-1): /* ��up */
                        printf("��up ");
                        break;
                    
                    default: /* up������ꍇ */
                        printf("%dup ", processes[i].nup);
                        break;
                }
                switch (processes[i].ndown) {
                    case 0: /* down��0�̏ꍇ */
                        break;

                    case (-1): /* ��down */
                        printf("��down ");
                        break;
                    
                    default: /* down������ꍇ */
                        printf("%ddown ", processes[i].ndown);
                        break;
                }
                switch (judge) {
                    case 0: /* h �\�� */
                        printf("%dh\n", hour);
                        break;
                    case 30: /*n.5h */
                        printf("%d.5h\n", hour);
                        break;
                    case 1: /* �ړ����Ԃ�0 */
                        printf("\n");
                        break;
                    default: /* min�\�� */
                        printf("%dmin\n", processes[i].duration);
                        break;
                }
                break;
// �����܂ł���km�̏ꍇ
            default: /* �ʏ��km */
                printf("%dkm ", processes[i].nkm);
                switch (processes[i].nup) {
                    case 0: /* up��0�̏ꍇ */
                        break;

                    case (-1): /* ��up */
                        printf("��up ");
                        break;
                    
                    default: /* up������ꍇ */
                        printf("%dup ", processes[i].nup);
                        break;
                }
                switch (processes[i].ndown) {
                    case 0: /* down��0�̏ꍇ */
                        break;

                    case (-1): /* ��down */
                        printf("��down ");
                        break;
                    
                    default: /* down������ꍇ */
                        printf("%ddown ", processes[i].ndown);
                        break;
                }
                switch (judge) {
                    case 0: /* h �\�� */
                        printf("%dh\n", hour);
                        break;
                    case 30: /*n.5h */
                        printf("%d.5h\n", hour);
                        break;
                    case 1: /* �ړ����Ԃ�0 */
                        printf("\n");
                        break;
                    default: /* min�\�� */
                        printf("%dmin\n", processes[i].duration);
                        break;
                }
                break;
        }
        currentTime = addTime(currentTime, processes[i].duration); //���̎������v�Z
    }
}

int main(void) {
/* 
    [���͂̎d��]

    [�J�n�����̐ݒ���@]

    �J�n������6��00���ɂ������Ƃ��͉��́uTime start = { , }�v��
    �uTime start = {6, 0}�v�Ƃ������ɏ���������D

    [TT�Ă̍���]

    Processs[]�̒�`�ő�P�����ɏꏊ�C��Q�����ɏ��(�o�������⒋�H)�C
    ��R�����ɋ���(km)�C��S������up�C��T������up�C��U������down�������D
    �����Œ��ӂȂ̂������Cup�Cdown�C���Ԃ͕K��"���p"�ŏ������ƁD
    ���Ɏ��Ԃ�"��"���Z�̎��Ԃ��������ƁD�S�p�ŏ����Ƃ��܂������܂���D

    �����Ŕ�km�C��up�C��down�ɂ������Ƃ���-1����͂���D�e���ڂ�0����͂���
    �Ƃ��̍��ڂ͕\������Ȃ��D������km��0�̏ꍇ��up�Cdown��0�ł��邽��
    ��Q�����̏��Ǝ��Ԃ������\�������D
    
    Process processes[] = {
        {"�ꏊ", "���", km(���p), up(���p), down(���p),  ����(���p)}
        ...
    }
    

    �Ⴆ�΁@����w �L���L�����p�X
            ��  12km 348up 31down 50min
            ������
            ...
            ~~~~

    �Ɠ��͂������Ƃ���

            (����w �L���L�����p�X)*1
            ��  ()*2 (12)*3 km (348)*4 up (31)*5 down (50)*6 min
            ������

    �̂悤��6�̃p�[�c�ɕ�����

    Process processes[] = {
        {"����w �L���L�����p�X", "", 12, 348, 31, 50},
        {"������", "...", ., ., ., .}
        ...
    }

    �̂悤�ɓ��͂���΂悢�D��̗�̂悤�ȏꍇ�͑������̏��͋󔒂ɂ���΂悢�D

    �܂��C�u��km�v�Ȃǂ��g���Ƃ��͑Ή�����ꏊ��-1����͂���D
*/
// ~~~~~~~~~~~~~~~~~~~~������艺��ҏW~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /* 1         {��,��}  */
    Time start = {6, 0}; // �J�n����

    /* �H���f�[�^�̃��X�g */
    Process processes[] = {
    /* 2 {"�ꏊ", "���", km, up, down ,����(���p�E��)}*/
        {"�N��","�o�������A���H",0, 0, 0, 60},
        {"����o��", "", 40, 300, 200, 90},
        {"�L���L�����p�X", "", -1, -1, -1, 10},
        {"�K���K", "���H", 0, 0, 0, 60},
        {"�K���K�o��", "", 237, 3624, 3000, 60*9+30},
        {"���R�`�w", "�x�e", 0, 0, 0, 30},
        

// ~~~~~~~~~~~~~~~~~~~~���������ҏW~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        {"�A�Q","",0}
    };

    /* �X�P�W���[���v�Z */
    calculateSchedule(start, processes, sizeof(processes)/sizeof(processes[0]));
    
    return 0;
}


