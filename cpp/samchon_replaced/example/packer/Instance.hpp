#pragma once
#include <samchon/protocol/Entity.hpp>

#include <samchon/library/StringUtil.hpp>
#include <samchon/library/XML.hpp>

namespace samchon
{
	namespace example
	{
		namespace packer
		{
			/**
			 * @brief A physical instance
			 *
			 * @details 
			 * <p> A physical instance having its own name, price, volume and weight. </p>
			 *
			 * <p> @image html cpp/example_packer.png
			 * @image latex cpp/example_packer.png </p>
			 *
			 * @author Jeongho Nam
			 */
			class Instance
				: public virtual protocol::Entity
			{
			private:
				typedef protocol::Entity super;

			protected:
				/**
				 * @brief Name represent the Instance
				 */
				std::string name;

				/**
				 * @brief Price of an instance -> 1,000 won
				*/
				int price;

				/**
				 * @brief Volume of an instance -> 130 cm^3
				 */
				int volume;

				/**
				 * @brief Weight of an instance -> 1,200 g
				 */
				int weight;

			public:
				/* ---------------------------------------------------------
					CONSTRUCTORS
				--------------------------------------------------------- */
				/**
				 * @brief Default Constructor.
				 */
				Instance()
					: super()
				{
				};

				/**
				 * @brief Construct from instance
				 *
				 * @param name Name of the instance
				 * @param price Price of the instance
				 * @param volume Volume of the instance
				 * @param weight Weight of the instance
				 */
				Instance(const std::string &name, int price, int volume, int weight)
					: super()
				{
					this->name = name;
					this->price = price;
					this->volume = volume;
					this->weight = weight;
				};

				virtual ~Instance() = default;

				virtual void construct(std::shared_ptr<library::XML> xml) override
				{
					this->name = xml->getProperty("name");
					this->price = xml->getProperty<int>("price");
					this->volume = xml->getProperty<int>("volume");
					this->weight = xml->getProperty<int>("weight");
				};

				/* ---------------------------------------------------------
					GETTERS
				--------------------------------------------------------- */
				/**
				 * @brief Get name
				 */
				auto getName() const -> std::string
				{
					return name;
				};

				/**
				 * @brief Get price
				 */
				auto getPrice() const -> int
				{
					return price;
				};

				/**
				 * @brief Get volume
				 */
				auto getVolume() const -> int
				{
					return volume;
				};

				/**
				 * @brief Get weight
				 */
				auto getWeight() const -> int
				{
					return weight;
				};

				/* ---------------------------------------------------------
					EXPORT
				--------------------------------------------------------- */
				virtual auto toXML() const -> std::shared_ptr<library::XML> override
				{
					std::shared_ptr<library::XML> &xml = super::toXML();
					xml->setProperty("name", name);
					xml->setProperty("price", price);
					xml->setProperty("volume", volume);
					xml->setProperty("weight", weight);

					return xml;
				};

				/**
				 * @brief Return a string represents the Instance
				 */
				virtual auto toString() const -> std::string
				{
					return library::StringUtil::substitute
					(
						"{1}: ${2}, {3}cm^3, {4}g",
						name, price, volume, weight
					);
				};
			};
		};
	};
};