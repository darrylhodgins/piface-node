#include <node.h>
#include <nan.h>

#include <v8.h>
#include <libpiface-1.0/pfio.h>
#include <string.h>

using namespace v8;

NAN_METHOD(PfioInit) {

	NanScope();

	pfio_init();

	NanReturnUndefined();
}

NAN_METHOD(PfioDeinit) {

	NanScope();

	pfio_deinit();

	NanReturnUndefined();
}

NAN_METHOD(PfioDigitalRead) {

	NanScope();

	uint8_t pin = args[0]->Uint32Value();
	uint8_t result = pfio_digital_read(pin);

	NanReturnValue(NanNew<Number>(result));
}

NAN_METHOD(PfioDigitalWrite) {

	NanScope();

	uint8_t pin = args[0]->Uint32Value();
	uint8_t val = args[1]->Uint32Value();
	pfio_digital_write(pin, val);

	NanReturnUndefined();
}

NAN_METHOD(PfioReadInput) {

	NanScope();

	uint8_t val = pfio_read_input();

	NanReturnValue(NanNew<Number>(val));
}

NAN_METHOD(PfioReadOutput) {

	NanScope();

	uint8_t val = pfio_read_output();

	NanReturnValue(NanNew<Number>(val));
}

NAN_METHOD(PfioWriteOutput) {

	NanScope();

	uint8_t val = args[0]->Uint32Value();
	pfio_write_output(val);

	NanReturnUndefined();
}

void init(Handle<Object> exports) {

	exports->Set(NanNew<String>("init"),
		NanNew<FunctionTemplate>(PfioInit)->GetFunction());
	exports->Set(NanNew<String>("deinit"),
		NanNew<FunctionTemplate>(PfioDeinit)->GetFunction());
	exports->Set(NanNew<String>("digital_read"),
		NanNew<FunctionTemplate>(PfioDigitalRead)->GetFunction());
	exports->Set(NanNew<String>("digital_write"),
		NanNew<FunctionTemplate>(PfioDigitalWrite)->GetFunction());
	exports->Set(NanNew<String>("read_input"),
		NanNew<FunctionTemplate>(PfioReadInput)->GetFunction());
	exports->Set(NanNew<String>("read_output"),
		NanNew<FunctionTemplate>(PfioReadOutput)->GetFunction());
	exports->Set(NanNew<String>("write_output"),
		NanNew<FunctionTemplate>(PfioWriteOutput)->GetFunction());

}

NODE_MODULE(pfio, init);