
/* --- JSON <=> ProtobufCMessage --- */

ProtobufCMessage *pbcdsk_from_json  (const ProtobufCMessageDescriptor *desc,
                                     ProtobufCAllocator *allocator,
                                     DskJson           *json,
				     DskError         **error);
DskJson          *pbcdsk_to_json    (const ProtobufCMessage  *pbc);


