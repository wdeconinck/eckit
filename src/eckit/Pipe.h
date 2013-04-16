#ifndef eckit_Pipe_h
#define eckit_Pipe_h

#include "eclib/machine.h"

#include "eckit/memory/NonCopyable.h"
#include "eckit/thread/Mutex.h"
#include "eckit/thread/ThreadControler.h"

//-----------------------------------------------------------------------------

namespace eckit {

//-----------------------------------------------------------------------------

template<class PAYLOAD>
class PipeTask;

template<class PAYLOAD>
struct OnePayload;

template<class PAYLOAD>
class Pipe : private NonCopyable {
public:

    typedef void (*Proc)(Pipe<PAYLOAD>&);

    // -- Contructors

    Pipe(long count = 2);

    // -- Destructor

    ~Pipe();

    // -- Methods

    void spawn(Proc proc);

    bool eof();
    void close();

    PAYLOAD& message();
    PAYLOAD& receive();
    void send();

private:

    bool   error();
    void   error(const string&);

    // -- Methods

    // -- Members

    Mutex  mutex_;

    long   count_;

    int ri_;
    int wi_;
    int pi_;


    bool   done_;
    bool   error_;
    string why_;

    OnePayload<PAYLOAD>* payloads_;
    ThreadControler* controler_;

    // -- Friends

    friend class PipeTask<PAYLOAD>;

};


//-----------------------------------------------------------------------------

} // namespace eckit

#include "eclib/Pipe.cc"

#endif