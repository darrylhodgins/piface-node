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

// Handle<Value> PfioInit(const Arguments& args) {
// 	NanScope();
// 	pfio_init();
// 	return scope.Close(Undefined());
// }

NAN_METHOD(PfioDeinit) {

	NanScope();

	pfio_deinit();

	NanReturnUndefined();
}

// Handle<Value> PfioDeinit(const Arguments& args) {
// 	NanScope();
// 	pfio_deinit();
// 	return scope.Close(Undefined());
// }

// Handle<Value> PfioDigitalRead(const Arguments& args) {
// 	NanScope();
// 	// uint8_t pin = Integer::New(args[0]->IntegerValue())->Value();
// 	uint8_t pin = args[0]->Uint32Value();
// 	uint8_t result = pfio_digital_read(pin);
// 	return scope.Close(Integer::New(result));
// }

NAN_METHOD(PfioDigitalRead) {

	NanScope();

	uint8_t pin = args[0]->Uint32Value();
	uint8_t result = pfio_digital_read(pin);

	NanReturnValue(NanNew<Number>(result));
}

// Handle<Value> PfioDigitalWrite(const Arguments& args) {
// 	NanScope();
// 	// uint8_t pin = Integer::New(args[0]->IntegerValue())->Value();
// 	uint8_t pin = args[0]->Uint32Value();
// 	// uint8_t val = Integer::New(args[1]->IntegerValue())->Value();
// 	uint8_t val = args[1]->Uint32Value();
// 	pfio_digital_write(pin, val);
// 	return scope.Close(Undefined());
// }

NAN_METHOD(PfioDigitalWrite) {

	NanScope();

	uint8_t pin = args[0]->Uint32Value();
	uint8_t val = args[1]->Uint32Value();
	pfio_digital_write(pin, val);

	NanReturnUndefined();
}

// Handle<Value> PfioReadInput(const Arguments& args) {
// 	NanScope();
// 	uint8_t val = pfio_read_input();
// 	return scope.Close(Integer::New(val));
// }

NAN_METHOD(PfioReadInput) {

	NanScope();

	uint8_t val = pfio_read_input();

	NanReturnValue(NanNew<Number>(val));
}

// Handle<Value> PfioReadOutput(const Arguments& args) {
// 	NanScope();
// 	uint8_t val = pfio_read_output();
// 	return scope.Close(Integer::New(val));
// }

NAN_METHOD(PfioReadOutput) {

	NanScope();

	uint8_t val = pfio_read_output();

	NanReturnValue(NanNew<Number>(val));
}

// Handle<Value> PfioWriteOutput(const Arguments& args) {
// 	NanScope();
// 	// uint8_t val = Integer::New(args[0]->IntegerValue())->Value();
// 	uint8_t val = args[0]->Uint32Value();
// 	pfio_write_output(val);
// 	return scope.Close(Undefined());
// }

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

