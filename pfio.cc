#include <node.h>
#include <v8.h>
#include <libpiface-1.0/pfio.h>

using namespace v8;

Handle<Value> PfioInit(const Arguments& args) {
        HandleScope scope;
	pfio_init();
        return scope.Close(Undefined());
}

Handle<Value> PfioDeinit(const Arguments& args) {
        HandleScope scope;
        pfio_deinit();
        return scope.Close(Undefined());
}

Handle<Value> PfioDigitalRead(const Arguments& args) {
        HandleScope scope;
	uint8_t pin = Integer::New(args[0]->IntegerValue())->Value();
        uint8_t result = pfio_digital_read(pin);
        return scope.Close(Integer::New(result));
}

Handle<Value> PfioDigitalWrite(const Arguments& args) {
        HandleScope scope;
        uint8_t pin = Integer::New(args[0]->IntegerValue())->Value();
	uint8_t val = Integer::New(args[1]->IntegerValue())->Value();
	pfio_digital_write(pin, val);
        return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("init"),
		FunctionTemplate::New(PfioInit)->GetFunction());
	exports->Set(String::NewSymbol("deinit"),
		FunctionTemplate::New(PfioDeinit)->GetFunction());
	exports->Set(String::NewSymbol("digital_write"),
		FunctionTemplate::New(PfioDigitalWrite)->GetFunction());
        exports->Set(String::NewSymbol("digital_read"),
                FunctionTemplate::New(PfioDigitalRead)->GetFunction());
}

NODE_MODULE(pfio, init)

