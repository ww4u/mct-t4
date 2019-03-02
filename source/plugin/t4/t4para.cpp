#include "t4para.h"

T4Para::T4Para()
{
    init();
}

void T4Para::init()
{
    mTerminalType = T4Para::e_terminal_f2;

    mAxisCurrents[0] = 3.5;
    mAxisCurrents[1] = 3.5;
    mAxisCurrents[2] = 3.5;
    mAxisCurrents[3] = 1.8;
    mAxisCurrents[4] = 1.5;

    for ( int i = 0; i < T4Para::_axis_cnt; i++ )
    {
        mAxisZero[i] = 0;
    }

    for ( int i = 0; i < T4Para::_axis_cnt; i++ )
    {
        mAxisSoftUpper[ i ] = 180;
        mAxisSoftLower[ i ] = -180;
    }

    mStepIndex = 6;
    mSpeed = 0.2;
    mCoord = e_coord_base;

    for ( int i =0; i < 3; i++ )
    {
        mCoordPara[i].mPx = 0;
        mCoordPara[i].mPy = 0;
        mCoordPara[i].mPz = 0;

        mCoordPara[i].mRa = 0;
        mCoordPara[i].mRb = 0;
        mCoordPara[i].mRc = 0;
    }

    mArmLength[0] = 263.8;
    mArmLength[1] = 255;
    mArmLength[2] = 250;

    mHomeSpeed = 20;
    mHomeTimeout = 120;

    mDefSpeed = 200;
    mDefAcc = 10;

    mMaxJointSpeed =  180;
    mMaxTerminalSpeed = 250;

    mbAxisPwr = true;
    mbMctEn = true;
}

double T4Para::velocity()
{
    return mMaxTerminalSpeed * mSpeed / 100;
}

int T4Para::serialOut( QXmlStreamWriter &writer )
{
    writer.writeStartElement("terminal");
        writer.writeTextElement( "type", QString::number( (int)mTerminalType ) );
    writer.writeEndElement();

    for ( int i = 0; i < T4Para::_axis_cnt; i++ )
    {
        writer.writeStartElement("axis");
            writer.writeTextElement( "current", QString::number( mAxisCurrents[i]) );
            writer.writeTextElement( "zero", QString::number( mAxisZero[i]) );

            writer.writeTextElement( "upper", QString::number( mAxisSoftUpper[i]) );
            writer.writeTextElement( "lower", QString::number( mAxisSoftLower[i]) );
        writer.writeEndElement();
    }

    //! coord
    writer.writeStartElement("coord");

    writer.writeTextElement( "type", QString::number( (int)mCoord ) );

    for ( int i = 0; i < 3; i++ )
    {
        writer.writeStartElement("para");

        writer.writeTextElement( "px", QString::number( mCoordPara[i].mPx ) );
        writer.writeTextElement( "py", QString::number( mCoordPara[i].mPy ) );
        writer.writeTextElement( "pz", QString::number( mCoordPara[i].mPz ) );

        writer.writeTextElement( "ra", QString::number( mCoordPara[i].mRa ) );
        writer.writeTextElement( "rb", QString::number( mCoordPara[i].mRb ) );
        writer.writeTextElement( "rc", QString::number( mCoordPara[i].mRc ) );

        writer.writeEndElement();
    }

    writer.writeEndElement();

    //! arm
    writer.writeStartElement("arm");
        writer.writeTextElement( "base", QString::number( mArmLength[0] ) );
        writer.writeTextElement( "big_arm", QString::number( mArmLength[1] ) );
        writer.writeTextElement( "little_arm", QString::number( mArmLength[2] ) );
    writer.writeEndElement();

    //! speed
    writer.writeStartElement("speed");
        writer.writeTextElement( "percent", QString::number( mSpeed ) );
        writer.writeTextElement( "step", QString::number( mStepIndex ) );
    writer.writeEndElement();

    //! home
    writer.writeStartElement("home");
        writer.writeTextElement( "speed", QString::number( mHomeSpeed ) );
        writer.writeTextElement( "timeout", QString::number( mHomeTimeout ) );
    writer.writeEndElement();

    //! default
    writer.writeStartElement("motion");
        writer.writeTextElement( "speed", QString::number( mDefSpeed ) );
        writer.writeTextElement( "acc", QString::number( mDefAcc ) );
    writer.writeEndElement();

    //! speed
    writer.writeStartElement("max_speed");
        writer.writeTextElement( "joint", QString::number( mMaxJointSpeed ) );
        writer.writeTextElement( "terminal", QString::number( mMaxTerminalSpeed ) );
    writer.writeEndElement();

    //! control
    writer.writeStartElement("cotrol");
        writer.writeTextElement( "driver_enable", QString::number( mbAxisPwr ) );
        writer.writeTextElement( "mct_enable", QString::number( mbMctEn ) );
    writer.writeEndElement();

    return 0;
}
int T4Para::serialIn( QXmlStreamReader &reader )
{
    int axisId = 0;
    while( reader.readNextStartElement() )
    {
        if ( reader.name() == "terminal" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "type" )
                {
                    mTerminalType = (eTerminalType)reader.readElementText().toInt();
                }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "axis" )
        {
            axisId++;
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "current" )
                {
                    Q_ASSERT( axisId <= _axis_cnt );
                    mAxisCurrents[ axisId - 1] = reader.readElementText().toDouble();
                }
                else if ( reader.name() == "zero" )
                {
                    Q_ASSERT( axisId <= _axis_cnt );
                    mAxisZero[ axisId - 1] = reader.readElementText().toDouble();
                }
                else if ( reader.name() == "upper" )
                {
                    Q_ASSERT( axisId <= _axis_cnt );
                    mAxisSoftUpper[ axisId - 1] = reader.readElementText().toDouble();
                }
                else if ( reader.name() == "lower" )
                {
                    Q_ASSERT( axisId <= _axis_cnt );
                    mAxisSoftLower[ axisId - 1] = reader.readElementText().toDouble();
                }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "coord" )
        {
            int id = -1;
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "type" )
                {
                    mCoord = (eCoordinateType)reader.readElementText().toInt();
                }
                else if ( reader.name() == "para" )
                {
                    id++;
                    while( reader.readNextStartElement() )
                    {
                        if ( reader.name() == "px" )
                        { mCoordPara[id].mPx = reader.readElementText().toDouble(); }
                        else if ( reader.name() == "py")
                        { mCoordPara[id].mPy = reader.readElementText().toDouble(); }
                        else if ( reader.name() == "pz")
                        { mCoordPara[id].mPz = reader.readElementText().toDouble(); }
                        else if ( reader.name() == "ra")
                        { mCoordPara[id].mRa = reader.readElementText().toDouble(); }
                        else if ( reader.name() == "rb")
                        { mCoordPara[id].mRb = reader.readElementText().toDouble(); }
                        else if ( reader.name() == "rc")
                        { mCoordPara[id].mRc = reader.readElementText().toDouble(); }
                        else
                        { reader.skipCurrentElement(); }
                    }
                }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "arm" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "base" )
                { mArmLength[0] = reader.readElementText().toDouble(); }
                else if ( reader.name() == "big_arm" )
                { mArmLength[1] = reader.readElementText().toDouble(); }
                else if ( reader.name() == "little_arm" )
                { mArmLength[2] = reader.readElementText().toDouble(); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "speed" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "percent" )
                { mSpeed = reader.readElementText().toDouble(); }
                else if ( reader.name() == "step" )
                { mStepIndex = reader.readElementText().toInt(); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "home" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "speed" )
                { mHomeSpeed = reader.readElementText().toDouble(); }
                else if ( reader.name() == "timeout" )
                { mHomeTimeout = reader.readElementText().toInt(); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "motion" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "speed" )
                { mDefSpeed = reader.readElementText().toDouble(); }
                else if ( reader.name() == "acc" )
                { mDefAcc = reader.readElementText().toInt(); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "max_speed" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "joint" )
                { mMaxJointSpeed = reader.readElementText().toDouble(); }
                else if ( reader.name() == "terminal" )
                { mMaxTerminalSpeed = reader.readElementText().toInt(); }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else if ( reader.name() == "control" )
        {
            while( reader.readNextStartElement() )
            {
                if ( reader.name() == "driver_enable" )
                { mbAxisPwr = reader.readElementText().toInt() > 0; }
                else if ( reader.name() == "mct_enable" )
                { mbMctEn = reader.readElementText().toInt() > 0; }
                else
                { reader.skipCurrentElement(); }
            }
        }
        else
        {
            reader.skipCurrentElement();
        }
    }

    return 0;
}
