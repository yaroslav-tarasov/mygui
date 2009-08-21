/*!
	@file
	@author		Albert Semenov
	@date		08/2009
	@module
*/
#ifndef __BASE_ANIMATION_NODE_H__
#define __BASE_ANIMATION_NODE_H__

#include <MyGUI.h>
#include "BaseGraphNode.h"
#include "IAnimationNode.h"

namespace demo
{

	class BaseAnimationNode : public wraps::BaseGraphNode
	{
	public:
		BaseAnimationNode(const std::string& _layout) :
			BaseGraphNode(_layout),
			mAnimationNode(0)
		{
		}

		void setAnimationNode(animation::IAnimationNode* _node)
		{
			mAnimationNode = _node;
			baseInitialiseAnimationNode();
		}

		animation::IAnimationNode* getAnimationNode()
		{
			return mAnimationNode;
		}

		virtual void addConnection(const std::string& _eventout, BaseAnimationNode* _node, const std::string& _eventin)
		{
		}

		virtual void removeConnection(const std::string& _eventout, BaseAnimationNode* _node, const std::string& _eventin)
		{
		}

		virtual void invalidateNode(BaseAnimationNode* _sender)
		{
		}

		/** Event : Invalidate node.\n
			signature : void method(BaseAnimationNode* _sender)
			@param _sender
		*/
		MyGUI::delegates::CDelegate1<BaseAnimationNode*> eventInvalidateNode;

	protected:
		virtual void baseInitialiseAnimationNode() { }

	private:
		animation::IAnimationNode* mAnimationNode;

	};

} // namespace demo

#endif // __BASE_ANIMATION_NODE_H__
