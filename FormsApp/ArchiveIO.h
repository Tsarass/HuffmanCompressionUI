#pragma once

#ifndef ARCHIVEIO_H
#define ARCHIVEIO_H

#include "HuffHelperClasses.h"
#include "WindowInfo.h"

int Compress(NewArchiveViewContainer^ fileInfo, System::ComponentModel::BackgroundWorker^ worker, System::ComponentModel::DoWorkEventArgs ^ e);
int Decompress(ExtractArchiveContainer^ fileInfo, System::ComponentModel::BackgroundWorker^ worker, System::ComponentModel::DoWorkEventArgs ^ e);

OpenArchiveContainer^ ReadArchiveHeader(System::String^ archivepath);

#endif