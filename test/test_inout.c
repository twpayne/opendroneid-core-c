/*
Copyright (C) 2019 Intel Corporation

SPDX-License-Identifier: Apache-2.0

Open Drone ID C Library

Maintainer:
Gabriel Cox
gabriel.c.cox@intel.com
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <opendroneid.h>

ODID_BasicID_encoded BasicID_enc;
ODID_BasicID_data BasicID;
ODID_BasicID_data BasicID_out;

ODID_Location_encoded Location_enc;
ODID_Location_data Location;
ODID_Location_data Location_out;

ODID_Auth_encoded Auth_enc;
ODID_Auth_data Auth;
ODID_Auth_data Auth_out;

ODID_SelfID_encoded SelfID_enc;
ODID_SelfID_data SelfID;
ODID_SelfID_data SelfID_out;

ODID_System_encoded System_enc;
ODID_System_data System_data;
ODID_System_data System_out;

void test_InOut()
{
    printf("\n-------------------------------------Source Data-----------------------------------\n");
    BasicID.IDType = ODID_IDTYPE_CAA_ASSIGNED_ID;
    BasicID.UAType = ODID_UATYPE_ROTORCRAFT;
    safe_copyfill(BasicID.UASID,"123456789012345678901", sizeof(BasicID.UASID));
    printf("BasicID\n-------\n");
    printBasicID_data(BasicID);
    encodeBasicIDMessage(&BasicID_enc, &BasicID);

    Location.Status = ODID_STATUS_AIRBORNE;
    Location.Direction = 215.7;
    Location.SpeedHorizontal = 5.4;
    Location.SpeedVertical = 5.25;
    Location.Latitude = 45.539309;
    Location.Longitude = -122.966389;
    Location.AltitudeBaro = 100;
    Location.AltitudeGeo = 110;
    Location.HeightType = ODID_HEIGHT_REF_OVER_GROUND;
    Location.Height = 80;
    Location.HorizAccuracy = createEnumHorizontalAccuracy(2.5f);
    Location.VertAccuracy = createEnumVerticalAccuracy(0.5f);
    Location.BaroAccuracy = createEnumVerticalAccuracy(1.5f);
    Location.SpeedAccuracy = createEnumSpeedAccuracy(0.5f);
    Location.TSAccuracy = createEnumTimestampAccuracy(0.2f);
    Location.TimeStamp = 3600.52;
    printf("\nLocation\n--------\n");
    printLocation_data(Location);
    encodeLocationMessage(&Location_enc, &Location);

    Auth.AuthType = ODID_AUTH_MPUID;
    Auth.DataPage = 0;
    safe_copyfill(Auth.AuthData, "1234567890123456789012", ODID_STR_SIZE);
    printf("\nAuth\n--------------\n");
    printAuth_data(Auth);
    encodeAuthMessage(&Auth_enc, &Auth);

    SelfID.DescType = ODID_DESC_TYPE_TEXT;
    safe_copyfill(SelfID.Desc,"DronesRUS: Real Estate",sizeof(SelfID.Desc));
    printf("\nSelfID\n------\n");
    printSelfID_data(SelfID);
    encodeSelfIDMessage(&SelfID_enc, &SelfID);

    System_data.LocationSource = ODID_LOCATION_SRC_TAKEOFF;
    System_data.remotePilotLatitude = Location.Latitude + 0.00001;
    System_data.remotePilotLongitude = Location.Longitude + 0.00001;
    System_data.GroupCount = 35;
    System_data.GroupRadius = 75;
    System_data.GroupCeiling = 176.9;
    System_data.GroupFloor = 41.7;
    printf("\nSystem\n------\n");
    printSystem_data(System_data);
    encodeSystemMessage(&System_enc, &System_data);
    printf("\n-------------------------------------Encoded Data-----------------------------------\n");
    printf("          0- 1- 2- 3- 4- 5- 6- 7- 8- 9- 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24\n");
    printf("BasicID:  ");
    printByteArray((uint8_t*) &BasicID_enc, ODID_MESSAGE_SIZE, 1);

    printf("Location: ");
    printByteArray((uint8_t*) &Location_enc, ODID_MESSAGE_SIZE, 1);

    printf("Auth:     ");
    printByteArray((uint8_t*) &Auth_enc, ODID_MESSAGE_SIZE, 1);

    printf("SelfID:   ");
    printByteArray((uint8_t*) &SelfID_enc, ODID_MESSAGE_SIZE, 1);

    printf("System:   ");
    printByteArray((uint8_t*) &System_enc, ODID_MESSAGE_SIZE, 1);

    printf("\n-------------------------------------Decoded Data-----------------------------------\n");
    // Now for the reverse -- decode test
    decodeBasicIDMessage(&BasicID_out, &BasicID_enc);
    printf("BasicID\n-------\n");
    printBasicID_data(BasicID_out);

    decodeLocationMessage(&Location_out, &Location_enc);
    printf("\nLocation\n--------\n");
    printLocation_data(Location_out);

    decodeAuthMessage(&Auth_out, &Auth_enc);
    printf("\nAuth\n-------\n");
    printAuth_data(Auth_out);

    decodeSelfIDMessage(&SelfID_out, &SelfID_enc);
    printf("\nSelfID\n------\n");
    printSelfID_data(SelfID_out);

    decodeSystemMessage(&System_out, &System_enc);
    printf("\nSystem\n------\n");
    printSystem_data(System_out);
    printf("\n-------------------------------------  End  -----------------------------------\n");

}