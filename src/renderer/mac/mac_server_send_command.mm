// Copyright 2010, Google Inc.
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

#import <Cocoa/Cocoa.h>

#include "renderer/mac/mac_server_send_command.h"

#import "mac/common.h"

#include "base/base.h"
#include "base/const.h"
#include "session/commands.pb.h"

namespace mozc {
namespace renderer {
namespace mac {
bool MacServerSendCommand::SendCommand(
    const mozc::commands::SessionCommand &command,
    mozc::commands::Output *output) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  NSConnection *connection =
      [NSConnection
        connectionWithRegisteredName:@ kProductPrefix "_1_Connection"
                                host:nil];
  const string command_string = command.SerializeAsString();
  NSData *sending_data = [NSData dataWithBytes:command_string.data()
                                        length:command_string.size()];
  id peer = [connection rootProxy];
  [peer setProtocolForProxy:@protocol(ServerCallback)];
  [peer rendererClicked:sending_data];
  [pool drain];
  return true;
}
}  // namespace mozc::renderer::mac
}  // namespace mozc::renderer
}  // namespace mozc

