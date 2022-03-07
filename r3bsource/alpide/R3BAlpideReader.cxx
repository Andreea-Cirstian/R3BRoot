/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/

#include "FairLogger.h"
#include "FairRootManager.h"

#include "R3BAlpideMappedData.h"
#include "R3BAlpideReader.h"
#include "R3BLogger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"
#include <iostream>

/**
 ** ext_h101_alpide.h was created by running
 ** $unpacker --ntuple=STRUCT_HH,RAW:ALPIDE,id=h101_ALPIDE,NOTRIGEVENTNO,ext_h101_alpide.h
 **/

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_alpide.h"
}

R3BAlpideReader::R3BAlpideReader(EXT_STR_h101_ALPIDE_onion* data, size_t offset)
    : R3BReader("R3BAlpideReader")
    , fNEvent(1)
    , fFileName("")
    , fInput(NULL)
    , ae(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("R3BAlpideMappedData"))
{
}

R3BAlpideReader::~R3BAlpideReader()
{
    R3BLOG(DEBUG1, "Destructor.");
    if (fArray)
        delete fArray;
}

Bool_t R3BAlpideReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    R3BLOG(INFO, "");
    /*
    EXT_STR_h101_ALPIDE_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_ALPIDE, 0);

    if (!ok)
    {
        R3BLOG(error, "Failed to setup structure information.");
        return kFALSE;
    }
    */

    // Register output array in tree
    FairRootManager::Instance()->Register("AlpideMappedData", "ALPIDE_Map", fArray, !fOnline);
    fArray->Clear();

    fInput = new ifstream(fFileName);
    if (!fInput->is_open())
    {
        R3BLOG(fatal, "Cannot open input file: " << fFileName);
    }
    else
    {

        R3BLOG(info, "Open input file: " << fFileName);
    }

    return kTRUE;
}

Bool_t R3BAlpideReader::Read()
{
    R3BLOG(DEBUG1, "Event data: " << fNEvent);

    if (fInput)
    {
        if (ae == 0)
            *fInput >> ae >> b >> c >> d >> e >> f >> g;

        while (!fInput->eof())
        {

            if (fNEvent == ae)
            {
                new ((*fArray)[fArray->GetEntriesFast()]) R3BAlpideMappedData(d + 1, e + 1, f + 1, g + 1);
            }
            else if (ae > fNEvent)
                goto next;

            *fInput >> ae >> b >> c >> d >> e >> f >> g;
        }
    }
next:

    // Read ALPIDE detectors
    /*   for (int d = 0; d < 6; d++)
           if (fData->SST[d]._ == 1024)
               for (int strip = 0; strip < fData->SST[d]._; ++strip)
               {
                   new ((*fArray)[fArray->GetEntriesFast()]) R3BAlpideMappedData(d, strip, fData->SST[d].E[strip]);
               }

              */

    fNEvent += 1;
    return kTRUE;
}

void R3BAlpideReader::Reset()
{
    // Reset the output array
    fArray->Clear();
}

ClassImp(R3BAlpideReader);