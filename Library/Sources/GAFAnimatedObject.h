#pragma once

#ifndef __GAF_ANIMATED_OBJECT_H__
#define __GAF_ANIMATED_OBJECT_H__

#include "GAFAnimation.h"
#include "GAFCollections.h"

#include "GAFDelegates.h"

class GAFAnimation;
class GAFSprite;
class GAFAnimator;
class GAFAnimatedObject;
class GAFAsset;

enum PCAnimationFPSType
{
    kGAFAnimationFPSType_15 = 15,
    kGAFAnimationFPSType_30 = 30,
    kGAFAnimationFPSType_60 = 60
};

enum GAFAnimatedObjectControlFlags
{
    kGAFAnimatedObjectControl_None = 0,
    // If specified, state of controlled object will be changed every frame (like it is by default) and then
    // animatedObject:didDisplayFrameWithSubobject: will be called
    kGAFAnimatedObjectControl_ApplyState = 1 << 0
};


class GAFAnimatedObject : public CCLayer, public GAFAnimation
{
protected:
    GAFAnimatedObject();
private:
    GAFAsset * _asset;

    SubObjects_t m_subObjects;
    SubObjects_t m_masks;

    int         m_stencilLayer;

    CaptureObjects_t m_capturedObjects;
    bool _animationsSelectorScheduled;
    GAFFramePlayedDelegate * _framePlayedDelegate;
    GAFAnimatedObjectControlDelegate * _controlDelegate;

    int numberOfGlobalFramesForOneAnimationFrame();
    int _extraFramesCounter;
    PCAnimationFPSType _FPSType;

public:
    ~GAFAnimatedObject();
    static GAFAnimatedObject * create(GAFAsset * anAsset);
    static GAFAnimatedObject * createAndRun(const std::string& gafPath, bool looped = false);

    bool init(GAFAsset * anAsset);
    void processAnimations(float dt);
    CCPoint pupilCoordinatesWithXSemiaxis(float anXSemiaxis, float anYSemiaxis, CCPoint aCenter, CCPoint anExternalPoint);
    void removeAllSubObjects();
    
    void instantiateObject(const AnimationObjects_t& objs, const AnimationMasks_t& masks);

    void setSubobjectsVisible(bool visible);

    const SubObjects_t& getSubojects() const;
    const SubObjects_t& getMasks() const;

    void animatorDidPlayedFrame(GAFAnimator * anAnimator, int aFrameNo);

    virtual void start();
    virtual void stop();
    virtual void processAnimation();
    /// Takes control over subobject, which means that every frame control delegate will be notified to decide
    /// what to do with captured external object
    /// @note it supports only objects for now, DOES NOT SUPPORT MASKS
    /// @param subobject name taken from "namedParts" section in config
    /// @param controlFlags flags specifying what played will do with subobjects controlled externally
    /// @returns YES if control was successfully taken and all future
    bool captureControlOverSubobjectNamed(const char * aName, GAFAnimatedObjectControlFlags aControlFlags);
    /// Releases control over subobject captured earlier	
    void releaseControlOverSubobjectNamed(const char * aName);

    void setFramePlayedDelegate(GAFFramePlayedDelegate * delegate);
    void setControlDelegate(GAFAnimatedObjectControlDelegate * delegate);
    CCRect realBoundingBoxForCurrentFrame();

    /// Returns subobject by it id
    GAFSprite * subObjectForInnerObjectId(unsigned int anInnerObjectId);
    /// Returns object id by it name, defined in NamedParts
    unsigned int objectIdByObjectName(const std::string& aName);

    CCSprite* renderCurrentFrameToTexture(bool usePOTTextures = false);

    void realizeFrame(CCNode* out, int frameIndex);

    //! 0 means all masked pixels will be marked as 1 and so on
    void setStencilLayer(int newLayer);

    //! 0 means all masked pixels will be marked as 1 and so on
    void incStencilLayer();

    //! 0 means all masked pixels will be marked as 1 and so on
    void decStencilLayer();

    //! 0 means all masked pixels will be marked as 1 and so on
    int  getStencilLayer() const;

    virtual void draw();

}; // GAFAnimatedObject

#endif // __GAF_ANIMATED_OBJECT_H__
