#ifndef INPUT_STREAM_H_
#define INPUT_STREAM_H_

#include "readable_chunk.h"

namespace io {

class InputStream {
  public:
    explicit InputStream(ReadableAbstruct* reader)
        : iov_(reader->iov()), reader_(reader) {
      index_ = offset_ = total_ = 0;
    }
    virtual ~InputStream() {
    }

    // return false iif no data can be read.
    // buf and len must be null.
    bool Next(const char** buf, uint64* len);

    void Skip(uint64 len);
    void Backup(uint64 len);

    // return the total number of bytes read since this object was created.
    int byteCount() const {
      return total_;
    }

  private:
    const std::vector<iovec> iov_;
    scoped_ref<ReadableAbstruct> reader_;

    uint32 index_;
    uint64 offset_;
    uint64 total_;

    DISALLOW_COPY_AND_ASSIGN(InputStream);
};
}
#endif /* INPUT_BUF_H_ */
