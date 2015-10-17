#include <node.h>
#include <nan.h>

#include <v8.h>
#include <libpiface-1.0/pfio.h>
#include <string.h>

using namespace v8;

NAN_METHOD(PfioInit) {

	Nan::HandleScope scope;

	pfio_init();

	info.GetReturnValue().SetUndefined();
}

NAN_METHOD(PfioDeinit) {

	Nan::HandleScope scope;

	pfio_deinit();

	info.GetReturnValue().SetUndefined();
}

NAN_METHOD(PfioDigitalRead) {

	Nan::HandleScope scope;

	uint8_t pin = info[0]->Uint32Value();
	uint8_t result = pfio_digital_read(pin);

	info.GetReturnValue().Set(Nan::New<Number>(result));
}

NAN_METHOD(PfioDigitalWrite) {

	Nan::HandleScope scope;

	uint8_t pin = info[0]->Uint32Value();
	uint8_t val = info[1]->Uint32Value();
	pfio_digital_write(pin, val);

	info.GetReturnValue().SetUndefined();
}

NAN_METHOD(PfioReadInput) {

	Nan::HandleScope scope;

	uint8_t val = pfio_read_input();

	info.GetReturnValue().Set(Nan::New<Number>(val));
}

NAN_METHOD(PfioReadOutput) {

	Nan::HandleScope scope;

	uint8_t val = pfio_read_output();

	info.GetReturnValue().Set(Nan::New<Number>(val));
}

NAN_METHOD(PfioWriteOutput) {

	Nan::HandleScope scope;

	uint8_t val = info[0]->Uint32Value();
	pfio_write_output(val);

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
