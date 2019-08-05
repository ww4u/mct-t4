#ifndef T4PARA_H
#define T4PARA_H

#include <QtCore>

class Coordinate
{
public:
    union
    {
        struct
        {
            double mPx,mPy,mPz;
            double mRa,mRb,mRc;
        };

        double mParas[6];
    };
};

class T4Para
{
public:
    enum eTerminalType
    {
        e_terminal_f2,
        e_terminal_f3,
        e_terminal_tip,
        e_terminal_a5,
        e_terminal_user
    };

    enum eCoordinateType
    {
        e_coord_base,
        e_coord_tool,
        e_coord_obj,
        e_coord_user,
    };

    enum eAxis5Range
    {
       e_range_270,
       e_range_360,
    };


public:
    T4Para();

public:
    void init();
    void rst();
    double velocity();

public:
    int serialOut( QXmlStreamWriter &writer );
    int serialIn( QXmlStreamReader &reader );

public:
    const static int _axis_cnt = 5;
    const static int _limit_axis_cnt = 4;

    eTerminalType mTerminalType;
    eAxis5Range mA5Range;

    float mAxisCurrents[ T4Para::_axis_cnt ];
    float mAxisIdleCurrents[ T4Para::_axis_cnt ];

    double mAxisZero[ T4Para::_axis_cnt ];

    bool mbAxisSoftEnable;
    double mAxisSoftUpper[ T4Para::_axis_cnt ];
    double mAxisSoftLower[ T4Para::_axis_cnt ];

<<<<<<< HEAD
    bool mbAxisSafeEnable;
    double mAxisSafeUpper[ T4Para::_axis_cnt ];
    double mAxisSafeLower[ T4Para::_axis_cnt ];

=======
    //! robot para
>>>>>>> a43ebcf5685501fbaef541db20e9b533fc2693de
    int mStepIndex;
    double mSpeed;      //! percent
    double mCSpeed;     //! percent
    eCoordinateType mCoord;

<<<<<<< HEAD
    Coordinate mCoordPara[10+2];
=======
    //! joint para
    int mJointStepIndex;
    double mJointSpeed;

    Coordinate mCoordPara[3];
>>>>>>> a43ebcf5685501fbaef541db20e9b533fc2693de

    double mArmLength[3];

    double mHomeSpeed, mHomeTimeout;

    double mMaxAcc, mMaxJerk;
    int    mAutoAcc;

    double mMaxJointSpeed;
    double mMaxTerminalSpeed;

    QList<double> mMaxJointSpeeds;

    bool mbAxisPwr, mbMctEn;

    int mSlowMult, mSlowDiv;

    float mPackagesAxes[4];     //! four delta angles for package

    //! digital inputs name
    QStringList listIoName;
};

#endif // T4PARA_H
