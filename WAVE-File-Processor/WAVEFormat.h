#pragma once

#include <cstdint>

typedef struct {
    int32_t chunkId; // ������ ������ �������� 0x52494646 (����� "RIFF")
    int32_t chunkSize; // 36 + ����� ������� �������� � ������
                       // ������ ������� 4 + (8 + FMTSize) + (8 + DATACHUNKINFOSize)
                       // �� ����� ������ ����� ���� 8 ����� �� �������� ���� chunkId 
    int32_t format; // ��� wav-����� �� ������ 0x57415645 (����� "WAVE")
} RIFFHEADER;

typedef struct {
    int32_t Id;   // ������ 0x666d7420 � ����� "fmt"
    int32_t Size; // ������ 16 ��� ���� PCM. �� ����� ������� ��������, �� ���� ���� ����� �����
    int16_t audioFormat;   // PCM = 1
    int16_t numChannels;   // Mono = 1, Stereo = 2
    int32_t sampleRate;    // ��������� 44100
    int32_t byteRate;      // == SampleRate * NumChannels * BitsPerSample/8
    int16_t blockAlign;    // == NumChannels * BitsPerSample/8
    int16_t bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
} FMT;

typedef struct {
    int32_t Id;   // 0x64617461 � ����� "data"
    int32_t Size; // == NumSamples * NumChannels * BitsPerSample/8, ������� ����� ���������
} DATACHUNKINFO;

typedef struct {
    RIFFHEADER header;
    FMT fmt;
    DATACHUNKINFO dataChunkInfo;
} WAVEINFO;
