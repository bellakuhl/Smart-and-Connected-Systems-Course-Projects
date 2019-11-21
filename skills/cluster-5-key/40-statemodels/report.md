#  State Models

Author: Isabella Kuhl, 2019-11-20

## Summary

In this skill I created a state diagram for the security fob quest. I did this for all possible (and reasonable) scenarios during fob and hub use.

## Sketches and Photos

Here is a diagram for the Finite State Machine for Quest 4:

![FSM](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-5-key/40-statemodels/images/FSM.png)

Here is the state table:

| Event/State      | Locked | Receive Credentials | Check Credentials | Unlocked | Send to server |
|------------------|--------|---------------------|-------------------|----------|----------------|
| Correct          | -----  | ---------           | Unlocked          | -----    | Unlocked       |
| Incorrect        | -----  | ---------           | Locked            | -----    | -------        |
| Message Lost     | -----  | Locked              | -------           | Locked   | Locked         |
| Message Received | -----  | Check Credentials   | -------           | -----    | -------        |
| Transmit         | -----  | ---------           | -------           | -----    | -------        |
| Time Out         | -----  | ---------           | -------           | Locked   | Locked         |


-----

## Reminders
- Repo is private
