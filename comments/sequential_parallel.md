The code and discussion is related to the [Blech example blinker](https://github.com/frameworklabs/blinker)

The follwing code - which is part of the `main` activity in the original example - sequentialises the concurrent execution of two activities in order to change the output `blinkerLeverPos`.

Although it is perfectly correct it is quite complicated. The sequential data-flow has to be organised explicitly.

```blech   
activity monitorBlinkerLever(rotation: int32, blinkerLeverMove: int32)(blinkerLeverPos: int32)
    var movedBlinkerLeverPos: int32
    var localBlinkerLeverPos = blinkerLeverPos
    
    cobegin
        run moveBlinkerLever(blinkerLeverMove, prev localBlinkerLeverPos)(movedBlinkerLeverPos)
    with
        run updateBlinkerLeverFromRotation(rotation, movedBlinkerLeverPos)(localBlinkerLeverPos)
    with
        repeat
            blinkerLeverPos = localBlinkerLeverPos
            await true
        end
    end
end
```

The need to change something sequentially in concurrent trails/threads is quite common. A control flow statement that allows sequentially concurrent execution could substiantially simplify the code.

The following code would `begin` with a step in the first activity and `then` execute a step in the second activity. That means it sequentially combines execution steps in each control flow.

```blech   
activity monitorBlinkerLever (rotation: int32, blinkerLeverMove: int32)
                             (blinkerLeverPos: int32)
    begin
        run moveBlinkerLever(blinkerLeverMove)(blinkerLeverPos)
    then
        run updateBlinkerLeverFromRotation(rotation)(blinkerLeverPos)
    end
end
```

Note that this "folding" of execution steps is strictly sequential and does not need causality analysis.
Furthermore the called sub-activities can be simplified too, because their is no need to explicitly organise the data flow. They just update the `blinkerLeverPos` if necessary.

```blech
activity moveBlinkerLever(blinkerLeverMove: int32)(blinkerLeverPos: int32)
    repeat
        if blinkerLeverMove == BLINKER_LEVER_MOVE_UP then
            blinkerLeverPos = cap(prevBlinkerLeverPos - 1, BLINKER_LEVER_POS_UP, BLINKER_LEVER_POS_DOWN)
        elseif blinkerLeverMove == BLINKER_LEVER_MOVE_DOWN then
            blinkerLeverPos = cap(prevBlinkerLeverPos + 1, BLINKER_LEVER_POS_UP, BLINKER_LEVER_POS_DOWN)
        end
        await true
    end
end


activity updateBlinkerLeverFromRotation(rotation: int32)(blinkerLeverPos: int32)
    var rotationSum: int32
    repeat
        if movedBlinkerLeverPos != BLINKER_LEVER_POS_CENTER then
            updateRotationSum(rotation)(rotationSum)

            if rotationSum <= -ROTATION_THRESHOLD 
            and movedBlinkerLeverPos == BLINKER_LEVER_POS_UP then
                blinkerLeverPos = BLINKER_LEVER_POS_CENTER
                rotationSum = 0
            elseif rotationSum >= ROTATION_THRESHOLD 
            and movedBlinkerLeverPos == BLINKER_LEVER_POS_DOWN then
                blinkerLeverPos = BLINKER_LEVER_POS_CENTER
                rotationSum = 0
            end
        end
        await true
    end
end
```

Currently, we (the Blech team) are discussing the extension of the language with such a control flow statement.

```blech 
    begin
        ... 
    then
        ...
    then     // more than one then possible
        ...
    end
``` 

It would terminate if one of the combined parts terminates in a step.
Different to the `cobegin` the parts would not finish their steps.

The preemption (`abort`) would become syntactic sugar.

```blech
    when condition abort
        ... // executes in steps
    end
    // go on here if condition becomes true
``` 
could be expressed as

```blech
    begin
        await condition
    then
        ... // executes in steps
    end
    // go on here if condition becomes true
```

The latest extension of the [example with a warning indicator](https://github.com/frameworklabs/blinker) could also be better seperated into an activity that controls the blinkers via the blinker lever and another activity that controls (overrides) the blinkers and the warning indicator when the warning button is pushed.

The extension of my [branch with internal access to sensor and actuators](https://github.com/schorg/blinker/tree/comments) could be structured as follows
```blech
@[EntryPoint]
singleton activity main()
    @[CInput (binding="sensor_input.blinker_warning_pushed", header="blinker_env.h")]
    extern let warningPushed: bool         
        
    @[COutput (binding="actuator_state.blinker_lever_pos", header="blinker_env.h")]
    extern var blinkerLeverPos: int32

    var rotation: int32
    cobegin     
        run monitorBlinkerLever(rotation)(blinkerLeverPos)
    with
        run monitorWheelPos()(rotation)
    with
        @[COutput (binding="actuator_state.blinker_left_on", header="blinker_env.h")]
        extern var leftBlinker: bool         
        @[COutput (binding="actuator_state.blinker_right_on", header="blinker_env.h")]
        extern var rightBlinker: bool         
        begin 
            run controlBlinkers(blinkerLeverPos)(leftBlinker, rightBlinker) 
        then
            // would update left and right blinker 
            // access to warningPushed and the warning indicator can be encapsulated.
            run controlWarningIndication()(leftBlinker, rightBlinker)  
        end
    end
end
````

