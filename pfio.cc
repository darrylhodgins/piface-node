#include <node.h>
#include <nan.h>

#include <v8.h>
#include <pifacedigital.h>
#include <string.h>

using namespace v8;

/**  PiFaceDigital hardware address (configure with jumpers: JP1 and JP2) */
const int hw_addr = 0;

NAN_METHOD(PfioInit) {

	NanScope();

	pifacedigital_open(hw_addr);

	NanReturnUndefined();
}

NAN_METHOD(PfioDeinit) {

	NanScope();

	pifacedigital_close(hw_addr);

	NanReturnUndefined();
}

NAN_METHOD(PfioDigitalRead) {

	NanScope();

	uint8_t pin = args[0]->Uint32Value();
	uint8_t result = pifacedigital_read_bit(pin,INPUT,hw_addr);

	NanReturnValue(NanNew<Number>(result));
}

NAN_METHOD(PfioDigitalWrite) {

	NanScope();

	uint8_t pin = args[0]->Uint32Value();
	uint8_t val = args[1]->Uint32Value();
	pifacedigital_write_bit(val,pin, OUTPUT, hw_addr);

	NanReturnUndefined();
}

NAN_METHOD(PfioReadInput) {

	NanScope();

	uint8_t val  = pifacedigital_read_reg(INPUT, hw_addr);

	NanReturnValue(NanNew<Number>(val));
}

NAN_METHOD(PfioReadOutput) {

	NanScope();

	uint8_t val = pifacedigital_read_reg(OUTPUT, hw_addr);

	NanReturnValue(NanNew<Number>(val));
}

NAN_METHOD(PfioWriteOutput) {

	NanScope();

	uint8_t val = args[0]->Uint32Value();
	pifacedigital_write_reg(val, OUTPUT, hw_addr);

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
