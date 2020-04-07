The `tick` function for the following Blech program 

```blech
@[EntryPoint]
activity(a: bool)(b: bool) returns bool
    await true
    return false
end
```
in file `returnInEntryPoint.blc` is missing a parameter for the return value.

Compiling this file with `blechc` generates the following `tick` function.

```c
void blc_blech_returnInEntryPoint_tick (const blc_bool blc_main_a,
                                        blc_bool *blc_main_b) {
    blc_main(blc_main_a, blc_main_b, &pc_1, &blc_main_retvar);
}
```

which does not take into account the return variable.