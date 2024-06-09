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
    char *distance; // �H���̋���
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

    for (int i = 0; i < numProcesses; i++) {
        printf("%02d:%02d %s\n",currentTime.hours, currentTime.minutes, processes[i].event);
        if (i == numProcesses - 1) break; // �Ō�̍H���̏ꍇ����\�����Ȃ�
        /* �Œ�̎��Ԃ̕\���̔���(min��h��) */
        int judge = processes[i].duration % 60;
        /* �ړ����Ԃ�0�̏ꍇ */
        if (processes[i].duration == 0) {
            judge = 1;
        }
        int hour = processes[i].duration / 60;
        switch(judge) {
            case 0: /* h �\�� */
                printf("  ��%s %dh\n", processes[i].distance, hour);
                break;
            case 30: /*n.5h */
                printf("  ��%s %d.5h\n", processes[i].distance, hour);
                break;
            case 1: /* �ړ����Ԃ�0 */
                printf("  ��%s \n", processes[i].distance);
                break;
            default:
                printf("  ��%s %dmin\n", processes[i].distance, processes[i].duration);
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

    Processs[]�̒�`�ő������ɏꏊ�C�������ɋ����C�A�b�v�⒋�H�C�����o���Ȃǂ̏��C
    ��O�����Ɏ��Ԃ������D�����Œ��ӂȂ̂����Ԃ͕K��"���p"��"��"���Z�̎��Ԃ��������ƁD
    �S�p�ŏ����Ƃ��܂������܂���D
    
    Process processes[] = {
        {"�ꏊ", "������up�̏��", ����(���p)}
        ...
    }
    

    �Ⴆ�΁@����w �L���L�����p�X
            ��  12km 348up 31down 50min
            ������
            ...
            ~~~~

    �Ɠ��͂������Ƃ���

            (����w �L���L�����p�X)*1
            ��  (12km 348up 31down)*2 (50)*3 min
            ������

    �̂悤��3�̃p�[�c�ɕ�����

    Process processes[] = {
        {"����w �L���L�����p�X", "12km 348up 31down", 50},
        {"������", "...", ...}
        ...
    }

    �̂悤�ɓ��͂���΂悢
*/
// ~~~~~~~~~~~~~~~~~~~~������艺��ҏW~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /* 1         {��,��}  */
    Time start = {6, 0}; // �J�n����

    /* �H���f�[�^�̃��X�g */
    Process processes[] = {
    /* 2 {"�ꏊ", "���", ����(���p�E��)}*/
        {"�K���K","���H", 80},
        

// ~~~~~~~~~~~~~~~~~~~~���������ҏW~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        {"�A�Q","",0}
    };

    /* �X�P�W���[���v�Z */
    calculateSchedule(start, processes, sizeof(processes)/sizeof(processes[0]));
    
    return 0;
}


