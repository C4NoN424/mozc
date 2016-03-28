// Copyright 2010-2016, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_DATA_MANAGER_DATASET_READER_H_
#define MOZC_DATA_MANAGER_DATASET_READER_H_

#include <map>
#include <string>

#include "base/string_piece.h"

namespace mozc {

class DataSetReader {
 public:
  DataSetReader();
  ~DataSetReader();

  // Initializes the reader from the binary image of dataset file and expected
  // magic number.  The caller is responsible to load the content of a dataset
  // file into memory, and |memblock| must outlive this instance.  Note: this
  // method doesn't verify checksum for performance.  One can separately call
  // VerifyChecksum().
  bool Init(StringPiece memblock, StringPiece magic);

  // Gets the byte data corresponding to |name|.  If the data for |name| doesn't
  // exist, returns false.
  bool Get(const string &name, StringPiece *data) const;

  // Verifies the checksum of binary image.
  static bool VerifyChecksum(StringPiece memblock);

 private:
  // The value points to a block of the specified |memblock|.
  map<string, StringPiece> name_to_data_map_;
};

}  // namespace mozc

#endif  // MOZC_DATA_MANAGER_DATASET_READER_H_
