#pragma once

#include <memory>
#include <utility>

namespace PreViewer {

		template <typename T>
		using PrePtr = std::shared_ptr<T>;
		template <typename T, typename ...Args>
		constexpr PrePtr<T> CreatePrePtr(Args&&... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
}