#pragma once

#ifndef __GAF_ASSET_H__
#define __GAF_ASSET_H__

#include "GAFCollections.h"
#include "GAFHeader.h"

#include "GAFDelegates.h"

using namespace cocos2d;

class GAFTextureAtlas;
class GAFAnimatedObject;
class GAFAnimationSequence;
class GAFAnimationFrame;

class GAFLoader;

class GAFAsset : public CCObject
{
private:
    TextureAtlases_t        m_textureAtlases;
    AnimationMasks_t        m_animationMasks;
    AnimationObjects_t      m_animationObjects;
    AnimationFrames_t       m_animationFrames;
    AnimationSequences_t    m_animationSequences;
    NamedParts_t            m_namedParts;
    GAFHeader               m_header;

    GAFTextureAtlas*        m_currentTextureAtlas;
    GAFTextureLoadDelegate* m_textureLoadDelegate;

private:
    float _usedAtlasContentScaleFactor;
    int _majorVersion;
    int _minorVersion;

public:
    /// Initializes asset with bGAF data

    bool                        initWithGAFFile(const std::string& filePath, GAFTextureLoadDelegate* delegate = NULL);

    void                        pushTextureAtlas(GAFTextureAtlas* atlas);
    void                        pushAnimationMask(unsigned int objectId, unsigned int elementAtlasIdRef);
    void                        pushAnimationObjects(unsigned int objectId, unsigned int elementAtlasIdRef);
    void                        pushAnimationFrame(GAFAnimationFrame* frame);
    void                        pushAnimationSequence(const std::string nameId, int start, int end);
    void                        pushNamedPart(unsigned int objectIdRef, const std::string& name);

    void                        setHeader(GAFHeader& h);
    const GAFHeader&            getHeader() const;

    const AnimationObjects_t&   getAnimationObjects() const;
    const AnimationMasks_t&     getAnimationMasks() const;
    const AnimationFrames_t&    getAnimationFrames() const;
    const NamedParts_t&         getNamedParts() const;

    /// get all of the sequences
    const AnimationSequences_t& getAnimationSequences() const;

    static GAFAsset*            create(const std::string& gafFilePath, GAFTextureLoadDelegate* delegate = NULL);

    GAFAsset();
    ~GAFAsset();
    /// total number of frames in animation
    int                         animationFramesCount() const;

    GAFTextureAtlas *           textureAtlas();

    /// get GAFAnimationSequence by name specified in editor
    const GAFAnimationSequence* getSequence(const std::string& name) const;

    /// get GAFAnimationSequence by last frame number in sequence	
    const GAFAnimationSequence* getSequenceByLastFrame(int frame) const;

    /// get GAFAnimationSequence by first frame number in sequence	
    const GAFAnimationSequence* getSequenceByFirstFrame(int frame) const;
    /// List of GAFAnimationFrame objects	
    static bool                 isAssetVersionPlayable(const char * version);

    GAFAnimatedObject *         createObject();
    GAFAnimatedObject *         createObjectAndRun(bool looped = false);

    /// desired content scale factor
    static float                desiredCsf();
    /// sets desired content scale factor
    static void                 setDesiredCsf(float csf);
    /// used content scale factor		
    float                       usedAtlasContentScaleFactor()const;

    void                        setTextureLoadDelegate(GAFTextureLoadDelegate* delegate);
};


#endif // __GAF_ASSET_H__
