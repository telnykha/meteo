//---------------------------------------------------------------------------

#ifndef MainCdf2H
#define MainCdf2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "FImage.h"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "nc_XML_Import.h"

#include "Cube3D.h"
#include <ActnList.hpp>
#include <System.Actions.hpp>
enum EView2D {eSourceData, eSourceCone, eIntepolatedCone, eSourceVirtical, eInterpolatedVertical, eInterpolatedHorizontal, eResultCell} ;
enum EView3D {e3dSourceData, e3dConeContours};
typedef struct
{
    double dist_x;
    int    step_ro;
    int    step_fi;
    bool   smooth;
    bool   contours;
}View2DOptions;
typedef struct
{
    int imageWidth;
    double Height;
    double Distance;
}TPlaneOptions;

typedef struct
{
	int         num;
	T3DPoint*   pts;
}T3DContour;
typedef struct   // массив структур вектора признаков
{
	int s;// square
	double p;//perimetr
	int cX;
	int cY;
	double teta;
	double mi;
	double ma;

}VectorP;

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TFImage *FImage1; // interpolation
    TOpenDialog *OpenDialog1;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton3;
    TSaveDialog *SaveDialog1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *N1;
    TMenuItem *Exit1;
    TMenuItem *View1;
    TMenuItem *Source1;
    TMenuItem *SourceCone;
    TMenuItem *SourceConeInter;
    TMenuItem *SourceVertical1;
    TMenuItem *SourceVerticalInter1;
    TPanel *Panel2;
    TStatusBar *StatusBar1;
    TChart *Chart1;
    TFastLineSeries *Series1;
    TChart *Chart2;
    TFastLineSeries *FastLineSeries1;
    TActionList *ActionList1;
    TAction *SourceViewAction;
    TAction *SourceConeViewAction;
    TAction *InterConeAction;
    TAction *SourceVerticalAction;
    TAction *InterVerticalAction;
    TAction *OptionsAction;
    TMenuItem *Tools1;
    TMenuItem *Options1;
    TMenuItem *N3DView1;
    TAction *Source3dViewAction;
    TAction *HContours3dViewAction;
    TMenuItem *Source3DData1;
    TMenuItem *Contours3DData1;
    TComboBox *ComboBox1;
    TLabel *Label3;
    TComboBox *ComboBox2;
    TLabel *Label1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton4;
    TTimer *Timer1;
    TSpeedButton *SpeedButton5;
    TAction *InterHorizontalAction;
    TMenuItem *N2;
    TAction *ResultCellsAction;
    TMenuItem *N3;
    TMenuItem *N4;
    TComboBox *ComboBox3;
	TPaintBox *PaintBox1;
	TSplitter *Splitter1;
	TPanel *Panel3;
	TListView *ListView1;
	TFImage *FImage2;
	TSplitter *Splitter2;
    void __fastcall SpeedButton1Click(TObject *Sender);
    void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall SpeedButton3Click(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall ComboBox2Change(TObject *Sender);
    void __fastcall FImage1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall SourceViewActionExecute(TObject *Sender);
    void __fastcall SourceConeViewActionExecute(TObject *Sender);
    void __fastcall SourceConeViewActionUpdate(TObject *Sender);
    void __fastcall SourceViewActionUpdate(TObject *Sender);
    void __fastcall InterConeActionExecute(TObject *Sender);
    void __fastcall InterConeActionUpdate(TObject *Sender);
    void __fastcall SourceVerticalActionExecute(TObject *Sender);
    void __fastcall SourceVerticalActionUpdate(TObject *Sender);
    void __fastcall InterVerticalActionExecute(TObject *Sender);
    void __fastcall InterVerticalActionUpdate(TObject *Sender);
    void __fastcall Panel1Resize(TObject *Sender);
    void __fastcall OptionsActionExecute(TObject *Sender);
    void __fastcall Source3dViewActionExecute(TObject *Sender);
    void __fastcall Source3dViewActionUpdate(TObject *Sender);
    void __fastcall HContours3dViewActionExecute(TObject *Sender);
    void __fastcall HContours3dViewActionUpdate(TObject *Sender);
    void __fastcall SpeedButton4Click(TObject *Sender);
    void __fastcall SpeedButton2Click(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall SpeedButton5Click(TObject *Sender);
    void __fastcall InterHorizontalActionExecute(TObject *Sender);
    void __fastcall InterHorizontalActionUpdate(TObject *Sender);
    void __fastcall ResultCellsActionExecute(TObject *Sender);
    void __fastcall ResultCellsActionUpdate(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ComboBox3Change(TObject *Sender);
	void __fastcall PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FImage1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);



private:	// User declarations
       	UnicodeString m_strDataPath;

        int       m_ncid;
		awpImage* m_source;  // исходное изображение
		awpImage* m_azmuth;
        double*   m_dist;
		awpImage* m_elev;
		// result
		//awpImage* m_result;

        int mr,mpsi;

        T3DTransform 		t;
        bool 	m_mdown;
        int	    m_dx;
        int 	m_dy;
        int     m_currentFrame;

        EView2D         m_2DViewOptions;
        View2DOptions   m_2DOptions;
        TPlaneOptions   m_planeOptions;

        EView3D         m_3DViewOptions;
        T3DPoint*       m_3DPoints;
        int             m_num3DPoints;

        T3DContour*     m_3DContours;
        int             m_num3DContours;

        int             m_max_lenght;

		TList          *FList;
		TList          *VecList;// список признаков дл€ каждой €чейки
		TList           *MapList;
        double         RLat; //координаты радара
        double         RLon; // координаты радара

        // Ќаходит ближайшую €чейку к заданной площадке
        VectorP* GetNearCell(double x, double y);


        void __fastcall DrawSource(int channel);
        void __fastcall DrawSourceCone(int channel);
        void __fastcall DrawSourceConeInter(int channel);

        void __fastcall Draw2DScene();

        void __fastcall DrawVerticalArea();
        void __fastcall Draw3DPoint(TCanvas* cnv, T3DPoint& p);
        void __fastcall DrawSourceCone3D(TCanvas* cnv);
        void __fastcall DrawInterCone3D(TCanvas* cnv);
        void __fastcall MakeSourceCone3D();
        void __fastcall MakeInterCone3D();
        void __fastcall DrawResultCells();
		void __fastcall DrawScene();

        void __fastcall MakeInterPic(double H, double R, awpImage* img);
        void __fastcall FindAlfaMaxMin(double& amin, double& amax);
        awpPoint __fastcall FindFiTheta(double fi, double theta);
        void __fastcall OpenNCFile(const char* lpFileName);
        void __fastcall DrawFlashes1(awpImage* image);
        awpImage* GetInterCone(int index);

		void __fastcall FindObjects(awpImage* image,awpImage*   image2);
		void __fastcall FImageResult(TList* VecList, TList * MapList);
		void __fastcall DrawResult(TList * MapList);

public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
