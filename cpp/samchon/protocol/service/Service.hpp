#pragma once
#include <samchon/API.hpp>

#include <samchon/protocol/IProtocol.hpp>

#include <string>
#include <samchon/protocol/service/ServiceKeeper.hpp>

#define KEEP_SERVICE_ALIVE auto &ucPair = __keepAlive();

namespace samchon
{
	namespace library
	{
		class XML;
		class SQLi;
	};
	namespace protocol
	{
		namespace service
		{
			class Client;

			/**
			 * @brief Service
			 */
			class SAMCHON_FRAMEWORK_API Service
				: public IProtocol
			{
				friend class Client;

			private:
				typedef IProtocol super;

			protected:
				/**
				 * @brief Required authority to access the service
				 */
				virtual auto REQUIRE_AUTHORITY() const -> int = NULL;
				
			private:
				/**
				 * @brief Client object Service is belonged to
				 */
				Client *client;

				std::string name;

			public:
				/**
				 * @brief Construct from Client
				 *
				 * @param client Client object Service is belonged to
				 */
				Service(Client*);
				virtual ~Service() = default;
				
				/**
				 * @brief Get Client
				 */
				auto getClient() const -> Client*;
				
			protected:
				auto __keepAlive() -> ServiceKeeper;

			public:
				/**
				 * @brief Shift the responsibility of sending an Invoke message to Client
				 *
				 * @param in An Invoke message to be sent to the (physical) client
				 */
				virtual void sendData(std::shared_ptr<Invoke>);
			};
		};
	};
};