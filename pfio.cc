#include <node.h>
#include <nan.h>

#include <v8.h>
#include <pifacedigital.h>
#include <string.h>

using namespace v8;

/**  PiFaceDigital hardware address (configure with jumpers: JP1 and JP2) */
const int hw_addr = 0;

NAN_METHOD(PfioInit) {

	Nan::HandleScope scope;

	pifacedigital_open(hw_addr);

	info.GetReturnValue().SetUndefined();
}

NAN_METHOD(PfioDeinit) {

	Nan::HandleScope scope;

	pifacedigital_close(hw_addr);

	info.GetReturnValue().SetUndefined();
}

NAN_METHOD(PfioDigitalRead) {

	Nan::HandleScope scope;

	uint8_t pin = info[0]->Uint32Value();
	uint8_t result = pifacedigital_read_bit(pin,INPUT,hw_addr);

	info.GetReturnValue().Set(Nan::New<Number>(result));
}

NAN_METHOD(PfioDigitalWrite) {

	Nan::HandleScope scope;

	uint8_t pin = info[0]->Uint32Value();
	uint8_t val = info[1]->Uint32Value();
	pifacedigital_write_bit(val,pin, OUTPUT, hw_addr);

	info.GetReturnValue().SetUndefined();
}

NAN_METHOD(PfioReadInput) {

	Nan::HandleScope scope;

	uint8_t val  = pifacedigital_read_reg(INPUT, hw_addr);

	info.GetReturnValue().Set(Nan::New<Number>(val));
}

NAN_METHOD(PfioReadOutput) {

	Nan::HandleScope scope;

	uint8_t val = pifacedigital_read_reg(OUTPUT, hw_addr);

	info.GetReturnValue().Set(Nan::New<Number>(val));
}

NAN_METHOD(PfioWriteOutput) {

	Nan::HandleScope scope;

	uint8_t val = info[0]->Uint32Value();
	pifacedigital_write_reg(val, OUTPUT, hw_addr);

	info.GetReturnValue().SetUndefined();
}

NAN_MODULE_INIT(init) {

	Nan::Set(target, Nan::New<String>("init").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioInit)->GetFunction());
	Nan::Set(target, Nan::New<String>("deinit").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioDeinit)->GetFunction());
	Nan::Set(target, Nan::New<String>("digital_read").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioDigitalRead)->GetFunction());
	Nan::Set(target, Nan::New<String>("digital_write").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioDigitalWrite)->GetFunction());
	Nan::Set(target, Nan::New<String>("read_input").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioReadInput)->GetFunction());
	Nan::Set(target, Nan::New<String>("read_output").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioReadOutput)->GetFunction());
	Nan::Set(target, Nan::New<String>("write_output").ToLocalChecked(),
		Nan::New<FunctionTemplate>(PfioWriteOutput)->GetFunction());

}

NODE_MODULE(pfio, init);
