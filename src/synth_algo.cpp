//
// Created by Abdulmajid, Olivier NASSER on 30/06/2025.
//
#include "../include/c0de_tracker.hpp"

namespace C0deTracker {
    namespace SynthSystem {

        SynthAlgoGraph::SynthAlgoGraph(SynthSystem::SynthNode *node) : root(node) {}

        SynthAlgoGraph::~SynthAlgoGraph() { delete this->root; }

        float SynthAlgoGraph::operator()(Oscillator* oscillators, uint_fast8_t oscillators_count, float a, float p, double t, double rt, float FMfeed) const {
            assert(this->root != nullptr && "At least one node must be assigned to the Algo graph");
            return this->root->process(oscillators, oscillators_count, a, p, t, rt, FMfeed);
        }

        void SynthAlgoGraph::setAlgo(SynthNode* algo) {
            delete this->root;
            this->root = algo;
        }

        OSCNode::OSCNode(uint_fast8_t index) : index(index){}

        float OSCNode::process(Oscillator *oscillators, uint_fast8_t oscillators_count, float a, float p, double t, double rt, float FMfeed) const {

            assert(this->index < oscillators_count && "Oscillator index must be between 0 and total used oscillators");
            return oscillators[this->index].oscillate(a, p, t, rt, FMfeed);
        }

        NodeOfTwo::NodeOfTwo(SynthNode *i1, SynthNode *i2) : input1(i1), input2(i2) {}

        NodeOfTwo::~NodeOfTwo() { delete this->input1; delete this->input2; }

        ADDNode::ADDNode(SynthNode *i1, SynthNode *i2) : NodeOfTwo(i1, i2) {}

        float ADDNode::process(Oscillator *oscillators, uint_fast8_t oscillators_count, float a, float p, double t, double rt, float FMfeed) const {
            return this->input1->process(oscillators, oscillators_count, a, p, t, rt, FMfeed)
                    + this->input2->process(oscillators, oscillators_count, a, p, t, rt, FMfeed);
        }

        SUBNode::SUBNode(SynthSystem::SynthNode *i1, SynthSystem::SynthNode *i2) : NodeOfTwo(i1, i2) {}

        float SUBNode::process(Oscillator *oscillators, uint_fast8_t oscillators_count, float a, float p, double t, double rt, float FMfeed) const {
            return this->input1->process(oscillators, oscillators_count, a, p, t, rt, FMfeed)
                   - this->input2->process(oscillators, oscillators_count, a, p, t, rt, FMfeed);
        }

        AMNode::AMNode(SynthSystem::SynthNode *i1, SynthSystem::SynthNode *i2) : NodeOfTwo(i1, i2) {}

        float AMNode::process(Oscillator *oscillators, uint_fast8_t oscillators_count, float a, float p, double t, double rt, float FMfeed) const {
            return this->input1->process(oscillators, oscillators_count, a, p, t, rt, FMfeed)
                   * this->input2->process(oscillators, oscillators_count, a, p, t, rt, FMfeed);
        }

        FMNode::FMNode(SynthNode *modulator, SynthNode *carrier) : NodeOfTwo(modulator, carrier) {}

        float FMNode::process(Oscillator *oscillators, uint_fast8_t oscillators_count, float a, float p, double t, double rt, float FMfeed) const {
            return this->input2->process(oscillators, oscillators_count, a, p, t, rt,
                                         FMfeed
                                         + this->input1->process(oscillators, oscillators_count, a, p, t, rt, FMfeed)
                                         );
        }
    }
}