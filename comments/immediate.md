In the current compiler a `run <activity>` guarantees that an `await` is contained.

The neccesary condition is that every thread/trail must stop at least at one await (must not be instantaneous). This is currently guaranteed by either an `await` or a `run <activity>`.

```blech
@[EntryPoint]
activity main()
    ... // no await necessary
    cobegin
        run <activity>  // at least one await
    with
        run <activity>  // at least one await
    end
    ... // no await necessary
end
```
The compiler keeps track of the complete run hierarchy from the entry point activity.

These conditions could be weakened. If an activity has an instantaneous path, such an activity could be classifed, for example as `immediate`.  An immediate activity does not guarantee to stop at an `await`.

The following program would be wrong, because the first forked thread/trail might not stop at an `await`. 
```blech
@[EntryPoint]
activity main()
    ... // no await necessary
    cobegin
        run <immediate activity>  // at least zero awaits
    with
        run <non-immediate activity>  // at least one await
    end
    ... // no await necessary
end
```
Adding an `await` in every path of the thread/trail would make the program correct.

```blech
@[EntryPoint]
activity main()
    ... // no await necessary
    cobegin
        run <immediate activity>  // at least zero awaits
        ...
        await <cond>
        ...
    with
        run <non-immediate activity>  // at least one await
    end
    ... // no await necessary
end
```

The compiler could keep track and could deduce/infer this immediate property.
The programmer could define an activity as `immediate` (new keyword to be chosen), telling the compiler I plan to use an instantaneous path - even if the current implementation is not instantaneous.
```blech
immediate activity noAwait()
    // allows and instantaneous path
end
```
Problem solved. Should we do this?
