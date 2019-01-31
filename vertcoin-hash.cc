#include <node.h>
#include <node_buffer.h>
#include <nan.h>

#include "Lyra2RE.h"
#include "scryptn.h"

using v8::Exception;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void SumLyra2REv2(const Nan::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Local<Object> target = args[0]->ToObject();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  lyra2re2_hash(input, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumLyra2REv3(const Nan::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Local<Object> target = args[0]->ToObject();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  lyra2re3_hash(input, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumLyra2RE(const Nan::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Local<Object> target = args[0]->ToObject();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  lyra2re_hash(input, output);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void SumScryptN(const Nan::FunctionCallbackInfo<Value>& args) {
 
  if(args.Length() < 1) {
    Nan::ThrowTypeError("1 argument expected");
    return;
  }  

  Local<Object> target = args[0]->ToObject();

  if(!node::Buffer::HasInstance(target)) {
    Nan::ThrowTypeError("Function expects buffer as input");
    return;
  }

  char* input = node::Buffer::Data(target);
  char* output = new char[32];

  scrypt_N_R_1_256(input, output, 2048, 1, 80);
  
  args.GetReturnValue().Set(Nan::NewBuffer(output, 32).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("SumLyra2REv3").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(SumLyra2REv3)->GetFunction());
  exports->Set(Nan::New("SumLyra2REv2").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(SumLyra2REv2)->GetFunction());
  exports->Set(Nan::New("SumLyra2RE").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(SumLyra2RE)->GetFunction());
  exports->Set(Nan::New("SumScryptN").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(SumScryptN)->GetFunction());
}

NODE_MODULE(vertcoinhash, Init) 
