//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "bass.h"
#include <algorithm>    // std::min_element, std::max_element

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "perfgrap"
#pragma resource "*.dfm"
TForm1 *Form1;


#define FREQ 44100
#define CHANS 1
#define BUFSTEP 200000	// memory allocation unit

int device;				// current input source
int input;				// current input source
char *recbuf=NULL;		// recording buffer
DWORD reclen;			// recording length

HRECORD rchan=0;		// recording channel
HSTREAM chan=0;			// playback channel

HWND win=NULL;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
					UnicodeString temp_tone[12]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","H"};
					for(int i=0;i<10;i++)
					{

						for(int j=0;j<12;j++)
						{
							unsigned char temp_str[20]={0};
							tone_mass[i*12+j]=temp_tone[j]+itoa(i,temp_str,10);
						}
					}
					/*int cc=0;
					for(float i=1;cc<10;i/=2)
					{
						octav_mass[cc]=(27.5*(pow(2.0,((float)i/12.0))));
						cc++;
					} */

					for(int i=0;i<111;i++)
					{
						octav_mass[i+9]=(27.5*(pow(2.0,((float)i/12.0))));
					}

                    int c,def;
                    BASS_DEVICEINFO di;
					for (c=0;BASS_RecordGetDeviceInfo(c,&di);c++) {
                        //MESS(16,CB_ADDSTRING,0,di.name);
						if (di.flags&BASS_DEVICE_DEFAULT) { // got the default device
                            //MESS(16,CB_SETCURSEL,c,0);
							def=c;
						}
					}
					InitDevice(def); // initialize default recording
					//StartRecording();
					//Sleep(100);


}
float buf[8192]={0};
float fft[8192]={0};
//---------------------------------------------------------------------------
// buffer the recorded data
BOOL CALLBACK RecordingCallback(HRECORD handle, const void *buffer, DWORD length, void *user)
{
    // increase buffer size if needed
    if ((reclen%BUFSTEP)+length>=BUFSTEP) {
        recbuf=(char *)realloc((char *)recbuf,((reclen+length)/BUFSTEP+1)*BUFSTEP);
        if (!recbuf) {
			rchan=0;
            //Error("Out of memory!");
            //MESS(10,WM_SETTEXT,0,"Record");
            return FALSE; // stop recording
		}
    }
    // buffer the data
    memcpy(recbuf+reclen,buffer,length);
	reclen+=length;

	int res=BASS_ChannelGetData(rchan,buf,BASS_DATA_FFT16384|BASS_DATA_FLOAT); // get the sample data (floating-point to avoid 8 & 16 bit processing)

	return TRUE; // continue recording
}

BOOL TForm1::InitDevice(int device)
{
    BASS_RecordFree(); // free current device (and recording channel) if there is one
    // initalize new device
	if (!BASS_RecordInit(device)) {

		return FALSE;
	}
    { // get list of inputs
        int c;
		const char *i;
		for (c=0;i=BASS_RecordGetInputName(c);c++) {
			if (!(BASS_RecordGetInput(c,NULL)&BASS_INPUT_OFF)) { // this one is currently "on"

			}
		}
    }
    return TRUE;
}
void TForm1::StartRecording()
{
	run=1;
    WAVEFORMATEX *wf;
    if (recbuf) { // free old recording
        BASS_StreamFree(chan);
        chan=0;
        free(recbuf);
        recbuf=NULL;
        // close output device before recording incase of half-duplex device
        BASS_Free();
    }
    // allocate initial buffer and make space for WAVE header
    recbuf=(char *)malloc(BUFSTEP);
    reclen=44;
    // fill the WAVE header
    memcpy(recbuf,"RIFF\0\0\0\0WAVEfmt \20\0\0\0",20);
    memcpy(recbuf+36,"data\0\0\0\0",8);
    wf=(WAVEFORMATEX*)(recbuf+20);
    wf->wFormatTag=1;
    wf->nChannels=CHANS;
    wf->wBitsPerSample=16;
    wf->nSamplesPerSec=FREQ;
    wf->nBlockAlign=wf->nChannels*wf->wBitsPerSample/8;
    wf->nAvgBytesPerSec=wf->nSamplesPerSec*wf->nBlockAlign;
    // start recording
	rchan=BASS_RecordStart(FREQ,CHANS,0,RecordingCallback,0);
    if (!rchan) {
        //Error("Couldn't start recording");
		free(recbuf);
		recbuf=0;
        return;
    }
    //MESS(10,WM_SETTEXT,0,"Stop");
}

void TForm1::StopRecording()
{
	run=0;
    BASS_ChannelStop(rchan);
    rchan=0;
	//MESS(10,WM_SETTEXT,0,"Record");
    // complete the WAVE header
    *(DWORD*)(recbuf+4)=reclen-8;
    *(DWORD*)(recbuf+40)=reclen-44;
    // enable "save" button
   // EnableWindow(DLGITEM(12),TRUE);
    // setup output device (using default device)
	if (!BASS_Init(-1,FREQ,0,win,NULL)) {
        //Error("Can't initialize output device");
        return;
    }

		BASS_Free();

}
#include <deque>
//std::deque<float *> mydeque ;
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{


	if (PaintBox1->Width < 1024) PaintBox1->Width = 1024;
	if (PaintBox1->Height < 100) PaintBox1->Height = 100;
	int Step = PaintBox1->Width/1024;

	Graphics::TBitmap *bmp = new Graphics::TBitmap();
	bmp->Width = PaintBox1->Width;
	bmp->Height = PaintBox1->Height;

	float max=*std::max_element(fft,fft+8192);
	float * ptr_max=std::max_element(fft,fft+8192);
	unsigned int pos=ptr_max-fft;
	EditAmp->Text=max;
	EditPos->Text=pos;
	int freq=(FREQ*pos)/(8192*2);



	for (int i = 0; i < 8192; i++)
	{
		fft[i]=buf[i]*TrackBarAmpli->Position;
		if(fft[i]>500)fft[i]=499;
	}

	if(fft[pos]>200)
	{
		EditTone->Text=gettone(freq);
		EditDif->Text=dif_without_abs;
		EditFreq->Text=freq;
	}
	for (int i = 0; i < 1024; i+=Step)
	{

		if(fft[i]>200)
		bmp->Canvas->Pen->Color = clRed;
		else
		bmp->Canvas->Pen->Color = clLime;
		bmp->Canvas->Rectangle(i,PaintBox1->Height,i+Step,PaintBox1->Height-fft[i]);
	}



	Application->ProcessMessages();
	PaintBox1->Canvas->Draw(0,0,bmp);
	delete bmp;
	bmp = NULL;


}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	StartRecording();
	//Chart1->
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	StopRecording();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ListBox1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{

	Beep(Edit4->Text.ToInt(),200);
}
//---------------------------------------------------------------------------
UnicodeString TForm1::gettone(float tone)
{

	float dif=220000;
	dif_without_abs=220000;
	int pos=0;
	for(int i=0;i<120;i++)
	{

		float temp=0;
		temp=fabs(tone-octav_mass[i]);
		if(temp<dif)
		{
			dif_without_abs=tone-octav_mass[i];
			dif=temp;
			pos=i;
		}
    }
	return tone_mass[pos];

}
