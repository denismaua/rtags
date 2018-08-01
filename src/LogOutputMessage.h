/* This file is part of RTags (http://rtags.net).

   RTags is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   RTags is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RTags.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef OutputMessage_h
#define OutputMessage_h

#include "RTagsMessage.h"
#include "QueryMessage.h"

class LogOutputMessage : public RTagsMessage
{
public:
    enum { MessageId = LogOutputId };

    LogOutputMessage(LogLevel level = LogLevel::Error, Flags<QueryMessage::Flag> flags = NullFlags)
        : RTagsMessage(MessageId), mLevel(level), mFlags(flags)
    {
    }

    LogLevel level() const { return mLevel; }
    Flags<QueryMessage::Flag> flags() const { return mFlags; }

    void encode(Serializer &serializer) const
    {
        serializer << mCommandLine << mLevel << mFlags.cast<unsigned long long>();
    }

    void decode(Deserializer &deserializer)
    {
        unsigned long long flags;
        deserializer >> mCommandLine >> mLevel >> flags;
        mFlags = Flags<QueryMessage::Flag>::construct(flags);
    }
private:
    LogLevel mLevel;
    Flags<QueryMessage::Flag> mFlags;
};

#endif
