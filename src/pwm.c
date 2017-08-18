#include <string.h>
#include <stdbool.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mraa.h>

static void
pwm_close(mrb_state *mrb, void *p){
    if (p != NULL){
        mraa_pwm_close((mraa_pwm_context)p);
    }
}

static struct mrb_data_type mrb_mraa_pwm_ctx_type = {
    "MraaPwmContext", pwm_close
};

mrb_value
mrb_mraa_pwm_init(mrb_state *mrb, mrb_value self){
    mrb_int pin;
    mrb_int chipid;
    mraa_pwm_context pwm;

    mrb_int argc;

    argc = mrb_get_args(mrb, "i|i", &pin, &chipid);

    if (argc == 1){
        pwm = mraa_pwm_init(pin);
    }
    else {
        pwm = mraa_pwm_init_raw(chipid, pin);
    }

    if (pwm == NULL){
        mrb_raisef(mrb, E_RUNTIME_ERROR, "Failed to initialize PIN:%S.", mrb_fixnum_value(pin));
    }

    DATA_TYPE(self) = &mrb_mraa_pwm_ctx_type;
    DATA_PTR(self) = pwm;

    return self;
}

mrb_value
mrb_mraa_pwm_write(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_float duty;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "f", &duty);
    result = mraa_pwm_write(pwm, duty);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_read(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;

    mrb_float duty;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    duty = mraa_pwm_read(pwm);

    return mrb_float_value(mrb, duty);
}

mrb_value
mrb_mraa_pwm_period(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_float period;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "f", &period);
    result = mraa_pwm_period(pwm, period);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_period_ms(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_int period;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "i", &period);
    result = mraa_pwm_period_ms(pwm, period);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_period_us(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_int period;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "i", &period);
    result = mraa_pwm_period_us(pwm, period);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_pulsewidth(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_float pulsewidth;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "f", &pulsewidth);
    result = mraa_pwm_pulsewidth(pwm, pulsewidth);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_pulsewidth_ms(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_int pulsewidth;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "i", &pulsewidth);
    result = mraa_pwm_pulsewidth_ms(pwm, pulsewidth);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_pulsewidth_us(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_int pulsewidth;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "i", &pulsewidth);
    result = mraa_pwm_pulsewidth_us(pwm, pulsewidth);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_enable(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_bool pwmen;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "b", &pwmen);
    result = mraa_pwm_enable(pwm, pwmen);

    return mrb_fixnum_value(result);
}

mrb_value
mrb_mraa_pwm_owner(mrb_state *mrb, mrb_value self){
    mraa_pwm_context pwm;
    mrb_bool owner;

    mraa_result_t result;

    Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);

    mrb_get_args(mrb, "b", &owner);
    result = mraa_pwm_owner(pwm, owner);

    return mrb_fixnum_value(result);
}

// mrb_value
// mrb_mraa_pwm_config_ms(mrb_state *mrb, mrb_value self){
//     mraa_pwm_context pwm;
//     mrb_int period;
//     mrb_float duty;
//
//     mraa_result_t result;
//
//     Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);
//
//     mrb_get_args(mrb, "if", &period, &duty);
//     result = mraa_pwm_config_ms(pwm, period, duty);
//
//     return mrb_fixnum_value(result);
// }
//
// mrb_value
// mrb_mraa_pwm_config_percent(mrb_state *mrb, mrb_value self){
//     mraa_pwm_context pwm;
//     mrb_int period;
//     mrb_float duty;
//
//     mraa_result_t result;
//
//     Data_Get_Struct(mrb, self, &mrb_mraa_pwm_ctx_type, pwm);
//
//     mrb_get_args(mrb, "if", &period, &duty);
//     result = mraa_pwm_config_percent(pwm, period, duty);
//
//     return mrb_fixnum_value(result);
// }
//
