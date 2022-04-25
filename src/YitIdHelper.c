/*
 * 版权属于：yitter(yitter@126.com)
 * 开源地址：https://github.com/yitter/idgenerator
 */

#include "YitIdHelper.h"
extern void SetIdGenerator(IdGeneratorOptions options) {
    SetOptions(options);
}

extern void SetWorkerId(uint32_t workerId) {
    IdGeneratorOptions options = BuildIdGenOptions(workerId);
    SetIdGenerator(options);
}

extern uint64_t NextId() {
    return GetIdGenInstance()->NextId();
//    IdGenerator *generator = GetIdGenInstance();
//    uint64_t id = generator->NextId();
//    SNOWFLAKE_FREE(generator);
//    return id;
}
