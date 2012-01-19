#include "Particle.hpp"
#include <sstream>
 
ParticleSystem::ParticleSystem( int width, int height )
{
	m_transparent = sf::Color( 0, 0, 0, 0 );
	m_image.Create( width, height, m_transparent );
	m_sprite.SetImage( m_image );
 
	m_position.x	= 0.5f * width;
	m_position.y	= 0.5f * height;
	m_particleSpeed	= 20.0f;
	m_dissolve	= false;
	m_dissolutionRate = 4;
	m_shape		= Shape::CIRCLE;
}
 
ParticleSystem::~ParticleSystem()
{
	for( ParticleIterator it = m_particles.begin(); it != m_particles.end(); it++ )
	{
		delete *it;
	}
}
 
void ParticleSystem::fuel( int particles )
{
	float angle;
	Particle* particle;
	for( int i = 0; i < particles; i++ )
	{
		particle = new Particle();
		particle->pos.x = m_position.x;
		particle->pos.y = m_position.y;
 
		switch( m_shape )
		{
		case Shape::CIRCLE:
			angle = m_randomizer.Random( 0.0f, 6.2832f );
			particle->vel.x = m_randomizer.Random( 0.0f, cos( angle ) );
			particle->vel.y = m_randomizer.Random( 0.0f, sin( angle ) );
			break;
		case Shape::SQUARE:
			particle->vel.x = m_randomizer.Random( -1.0f, 1.0f );
			particle->vel.y = m_randomizer.Random( -1.0f, 1.0f );
			break;
		default:
			particle->vel.x = 0.5f; // Easily detected
			particle->vel.y = 0.5f; // Easily detected
		}
 
		if( particle->vel.x == 0.0f && particle->vel.y == 0.0f )
		{
			delete particle;
			continue;
		}
 
		particle->color = sf::Color::Red;
		//particle->color.r = m_randomizer.Random( 0, 255 );
		//particle->color.g = m_randomizer.Random( 0, 255 );
		//particle->color.b = m_randomizer.Random( 0, 255 );
		m_particles.push_back( particle );
	}
}
 
void ParticleSystem::update()
{
	float time = m_clock.GetElapsedTime();
	m_clock.Reset();
 
	for( ParticleIterator it = m_particles.begin(); it != m_particles.end(); it++ )
	{
		(*it)->vel.x += m_gravity.x * time;
		(*it)->vel.y += m_gravity.y * time;
 
		(*it)->pos.x += (*it)->vel.x * time * m_particleSpeed;
		(*it)->pos.y += (*it)->vel.y * time * m_particleSpeed;
 
		if( m_dissolve ) (*it)->color.a -= static_cast<sf::Uint8> (m_dissolutionRate);
 
		if( (*it)->pos.x > m_image.GetWidth() || (*it)->pos.x < 0 || (*it)->pos.y > m_image.GetHeight() || (*it)->pos.y < 0 || (*it)->color.a < 10 )
		{
			delete (*it);
			it = m_particles.erase( it );
			if( it == m_particles.end() ) return;
		}
	}
}
 
void ParticleSystem::render()
{
	for( ParticleIterator it = m_particles.begin(); it != m_particles.end(); it++ )
	{
		m_image.SetPixel( (int)(*it)->pos.x, (int)(*it)->pos.y, (*it)->color );
	}
}
 
void ParticleSystem::remove()
{
	for( ParticleIterator it = m_particles.begin(); it != m_particles.end(); it++ )
	{
		m_image.SetPixel( (int)(*it)->pos.x, (int)(*it)->pos.y, m_transparent );
	}
}
 
std::string ParticleSystem::getNumberOfParticlesString()
{
	std::ostringstream oss;
	oss << m_particles.size();
	return oss.str();
}
